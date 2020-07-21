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

bool TCPClient::connectTo(QString address, quint16 port)
{
    m_client.connectToHost(address, port);
    return m_client.waitForConnected();
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

bool TCPClient::isValid()
{
    return m_client.isValid();
}

void TCPClient::onConnected()
{
    if(m_pMsgHandle)
    {
        TextMessage msg("CONN", m_client.peerAddress().toString() + ":" + QString::number(m_client.peerPort()));
        m_pMsgHandle->handle(&m_client, msg);
    }
}
void TCPClient::onDisconnected()
{
    if(m_pMsgHandle)
    {
        TextMessage msg("DSCN", "");
        m_pMsgHandle->handle(&m_client, msg);
    }
    m_Assembler.reset();
}
void TCPClient::onBytesWritten(qint64 bytes)
{

}
void TCPClient::onReadyRead()
{
    char buf[256] = {0};
    int len = 0;

    while( (len = m_client.read(buf, sizeof(buf))) > 0 )
    {
        m_Assembler.prepare(buf, len);

        QSharedPointer<TextMessage> msg = NULL;
        while( NULL != (msg = m_Assembler.assemble()) )
        {
            if( NULL != m_pMsgHandle )
            {
                m_pMsgHandle->handle(&m_client, *msg);
            }
        }
    }
}

void TCPClient::onError(QAbstractSocket::SocketError socketError)
{

}
