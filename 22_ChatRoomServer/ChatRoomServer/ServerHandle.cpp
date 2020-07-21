#include "ServerHandle.h"

ServerHandle::ServerHandle()
{
    m_mapHandle.insert("CONN", CONN_handle);
    m_mapHandle.insert("DSCN", DSCN_handle);
    m_mapHandle.insert("LGIN", LGIN_handle);
    m_mapHandle.insert("MSGA", MSGA_handle);
}

void ServerHandle::handle(QTcpSocket* socket, TextMessage& message)
{
    qDebug() << socket;
    qDebug() << message.type();
    qDebug() << message.data();

    if(m_mapHandle.contains(message.type()))
    {
        MsgHandle handle = m_mapHandle.value(message.type());

        (this->*handle)(socket, message);
    }
}

void ServerHandle::CONN_handle(QTcpSocket* socket, TextMessage& message)
{

}
void ServerHandle::DSCN_handle(QTcpSocket* socket, TextMessage& message)
{
    for(int i=0; i<m_Nodelist.size(); i++)
    {
        if(socket == m_Nodelist[i]->clientSocket)
        {
            m_Nodelist[i]->clientSocket = NULL;
            break;
        }
    }
}
void ServerHandle::LGIN_handle(QTcpSocket* socket, TextMessage& message)
{
    int index = -1;
    index = message.data().indexOf('\r');
    QString result;

    QString id = message.data().mid(0, index);
    QString pwd = message.data().mid(index+1);

    index = -1;
    for(int i=0; i<m_Nodelist.size(); i++)
    {
        if(id ==  m_Nodelist.at(i)->id)
        {
            index = i;
            break;
        }
    }

    if(-1 != index)
    {
        if(pwd == m_Nodelist.at(index)->pwd)
        {
            result = "LIOK";
            m_Nodelist.at(index)->clientSocket = socket;
        }
        else
        {
            result = "LIER";
        }
    }
    else
    {
        Node* newNode = new Node();
        if(newNode)
        {
            newNode->id = id;
            newNode->pwd = pwd;
            newNode->clientSocket = socket;

            m_Nodelist.append(newNode);

            result = "LIOK";
        }
        else
        {
            result = "LIER";
        }
    }

    socket->write(TextMessage(result, id).serialize());
}

void ServerHandle::MSGA_handle(QTcpSocket* socket, TextMessage& message)
{
    const QByteArray& ba = message.serialize();
    for(int i=0; i<m_Nodelist.size(); i++)
    {
        if(NULL != m_Nodelist[i]->clientSocket)
        {
            m_Nodelist[i]->clientSocket->write(ba);
        }
    }
}
