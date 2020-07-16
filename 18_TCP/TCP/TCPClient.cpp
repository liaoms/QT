#include "TCPClient.h"
#include <QDebug>

TCPClient::TCPClient(QObject *parent) : QObject(parent)
{
    connect(&m_client, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&m_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&m_client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&m_client, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
}

TCPClient::~TCPClient()
{

}

void TCPClient::connectTo(QString address, quint16 port)
{
    m_client.connectToHost(address, port);
}

void TCPClient::write(QString str)
{
    if(m_client.state() == QAbstractSocket::ConnectedState)
    {
        m_client.write(str.toLatin1());
    }
}

void TCPClient::close()
{
    if(m_client.state() == QAbstractSocket::ConnectedState)
    {
        m_client.close();
    }
}

void TCPClient::onConnected()
{
    qDebug() << "TCPClient::onConnected()";

}
void TCPClient::onDisconnected()
{
    qDebug() << "TCPClient::onDisconnected()";
}
void TCPClient::onBytesWritten(qint64 bytes)
{
    qDebug() << "TCPClient::onBytesWritten : " << bytes;
}
void TCPClient::onReadyRead()
{
    char buf[256] = {0};
    m_client.read(buf, 256);
    qDebug() << "TCPClient::onReadyRead(), reciv:" << buf;
}
