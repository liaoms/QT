#include "TCPServer.h"
#include <QHostAddress>


TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    m_map.clear();
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
            delete m_map.take(client);
            client->close();
        }

        m_server.close();
    }
}

void TCPServer::setHandle(TxtMsgHandle* handle)
{
    m_pMsgHandle = handle;
}

void TCPServer::onNewConnection()
{
    QTcpSocket* newClient = m_server.nextPendingConnection();
    TxtMsgAssembler* newAssembler = new TxtMsgAssembler;
    if(NULL != newClient)
    {
        connect(newClient, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(newClient, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        connect(newClient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(newClient, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
        connect(newClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

        m_map.insert(newClient, newAssembler);

        if(m_pMsgHandle)
        {
            TextMessage msg("CONN", newClient->peerAddress().toString() + ":" +  QString::number(newClient->peerPort()));
            m_pMsgHandle->handle(newClient, msg);
        }
    }

}
void TCPServer::onAcceptError(QAbstractSocket::SocketError socketError)
{

}

void TCPServer::onConnected()
{

}
void TCPServer::onDisconnected()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());

    if( tcp != NULL )
    {
        if(m_pMsgHandle)
        {
            TextMessage msg("DSCN", " ");
            m_pMsgHandle->handle(tcp, msg);
        }
        delete m_map.take(tcp);
    }
}
void TCPServer::onBytesWritten(qint64 bytes)
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());
}
void TCPServer::onReadyRead()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());
    char buf[256] =  {0};
    int len = 0;

    if( tcp != NULL )
    {
        TxtMsgAssembler* pAssembler = m_map[tcp];
        while( (len = tcp->read(buf, 256)) > 0 )
        {
            if(NULL != pAssembler)
            {
                pAssembler->prepare(buf, len);
            }

            QSharedPointer<TextMessage> msg = NULL;
            while( NULL != (msg = pAssembler->assemble()) )
            {
                if( NULL != m_pMsgHandle )
                {
                    m_pMsgHandle->handle(tcp, *msg);
                }
            }
        }
    }
}

void TCPServer::onError(QAbstractSocket::SocketError socketError)
{
    //qDebug() << socketError;
}


