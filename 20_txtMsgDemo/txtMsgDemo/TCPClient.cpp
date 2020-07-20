#include "TCPClient.h"
#include <QHostAddress>
#include <QDebug>

TCPClient::TCPClient(QObject *parent) : QObject(parent)
{
    connect(&m_client, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&m_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&m_client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&m_client, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(&m_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

TCPClient::~TCPClient()
{

}

void TCPClient::connectTo(QString address, quint16 port)
{
    m_client.connectToHost(address, port);
    m_client.waitForConnected();
}

void TCPClient::write(TextMessage& msg)
{
    QByteArray ba = msg.serialize();
    m_client.write(ba);
}

void TCPClient::close()
{
    m_client.close();
}

void TCPClient::setHandle(TxtMsgHandle* handle)
{
    m_pMsgHandle = handle;
}

void TCPClient::onConnected()
{
    qDebug() << "client: connect to " << (m_client.peerAddress()).toString() << ":" << m_client.peerPort() << "succeed!";
}
void TCPClient::onDisconnected()
{
    qDebug() << "client: disconnect from " << (m_client.peerAddress()).toString() << ":" << m_client.peerPort();
    m_Assembler.reset();
}
void TCPClient::onBytesWritten(qint64 bytes)
{
    qDebug() << "client: write [" << bytes << "] bytes to" << (m_client.peerAddress()).toString() << ":" << m_client.peerPort() << "succeed!";
}
void TCPClient::onReadyRead()
{
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());
    char buf[256] = {0};
    m_client.read(buf, 256);
    qDebug() << "client: read [" << buf << "] from " << (m_client.peerAddress()).toString() << ":" << m_client.peerPort() << "succeed!";

    QSharedPointer<TextMessage> msg = m_Assembler.assemble(buf, strlen(buf));

    if(!msg.isNull())
    {
        m_pMsgHandle->handle(tcp, *msg);
    }
}

void TCPClient::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Client : Error [" << socketError << "]";
}
