#include "ServerHandle.h"

ServerHandle::ServerHandle()
{
    m_mapHandle.insert("CONN", CONN_handle);
    m_mapHandle.insert("DSCN", DSCN_handle);
    m_mapHandle.insert("LGIN", LGIN_handle);
    m_mapHandle.insert("MSGA", MSGA_handle);
    m_mapHandle.insert("MSGP", MSGP_handle);
}

//获取在线用户
QString ServerHandle::getOnlineUserId()
{
    QString ret = "";
    for(int i=0; i<m_Nodelist.size(); i++)
    {
        if(m_Nodelist[i]->clientSocket != NULL)
        {
            ret.append(m_Nodelist[i]->id);
            ret.append('\r');
        }
    }

    ret = ret.mid(0, ret.length()-1);
    return ret;
}

//发送消息到所有在线用户
void ServerHandle::SendToAllOnLine(TextMessage& message)
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

//断开连接处理
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

    QString usr = getOnlineUserId();

    TextMessage msg("USER", usr);

    SendToAllOnLine(msg);

}

//接收登录信息
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

    if("LIOK" == result)
    {
        QString usr = getOnlineUserId();

        TextMessage msg("USER", usr);

        SendToAllOnLine(msg);
    }
}

//转发消息到所有用户
void ServerHandle::MSGA_handle(QTcpSocket* socket, TextMessage& message)
{
    SendToAllOnLine(message);
}

//转发消息到私有用户
void ServerHandle::MSGP_handle(QTcpSocket* socket, TextMessage& message)
{
    QStringList list = message.data().split('\r');

    QString data = list.last();

    list.removeLast();
    for(int i=0; i<list.size(); i++)
    {
        for(int j=0; j<m_Nodelist.size(); j++)
        {
            if( (list[i] == m_Nodelist[j]->id) && (m_Nodelist[j]->clientSocket != NULL) )
            {
                TextMessage msg("MSGP", data);
                m_Nodelist[j]->clientSocket->write(msg.serialize());
                break;
            }
        }
    }

}
