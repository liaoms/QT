#include "TCPServer.h"
#include <QHostAddress>


TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    m_ClienList.clear();
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(&m_server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onAcceptError(QAbstractSocket::SocketError)));
}

TCPServer::~TCPServer()
{
    stop();
}

void TCPServer::start(int port)
{
    if(!m_server.isListening())
    {
        m_server.listen(QHostAddress::Any, port);
    }
}
void TCPServer::stop()
{
    if(!m_server.isListening())
    {
        const QObjectList list = m_server.children();

        for(int i=0; i<list.size(); i++)
        {
            QTcpSocket* client = dynamic_cast<QTcpSocket*>(list[i]);
            client->close();
        }

        m_server.close();
    }
}

void TCPServer::onNewConnection()
{
    QTcpSocket* newClient = m_server.nextPendingConnection();
    if(NULL != newClient)
    {
        connect(newClient, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(newClient, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(newClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(newClient, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
        connect(newClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

        m_ClienList.append(newClient);

        qDebug() << "client IP:" << (newClient->peerAddress()).toString();
        qDebug() << "client Port" << newClient->peerPort();
    }

}
void TCPServer::onAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << socketError;
}

void TCPServer::onConnected()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());

    if( tcp != NULL )
    {
        qDebug() << "onConnected";
        qDebug() << "Local Address:" << (tcp->localAddress()).toString();
        qDebug() << "Local Port:" << tcp->localPort();
    }
}
void TCPServer::onDisconnected()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());

    if( tcp != NULL )
    {
        qDebug() << (tcp->peerAddress()).toString() << ":" << tcp->peerPort() << " onDisconnected";
        m_ClienList.removeAll(tcp);
    }
}
void TCPServer::onBytesWritten(qint64 bytes)
{
    qDebug() << "onBytesWritten:" << bytes;
}
void TCPServer::onReadyRead()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());
    char buf[256] =  {0};

    if( tcp != NULL )
    {
        qDebug() << (tcp->peerAddress()).toString() << ":" << tcp->peerPort() << " onDataReady:" << tcp->read(buf, sizeof(buf)-1);
        qDebug() << "Data:" << buf;
    }
}

void TCPServer::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << socketError;
}


