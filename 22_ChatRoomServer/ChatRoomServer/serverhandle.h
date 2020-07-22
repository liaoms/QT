#ifndef SERVERHANDLE_H
#define SERVERHANDLE_H

#include "TxtMsgHandle.h"
#include "TextMessage.h"
#include <QTcpSocket>
#include <QList>
#include <QMap>

class ServerHandle : public TxtMsgHandle
{
private:
    typedef void (ServerHandle::*MsgHandle)(QTcpSocket*, TextMessage&);
    struct Node
    {
        QString id;
        QString pwd;
        QTcpSocket* clientSocket;

        Node()
        {
            id.clear();
            pwd.clear();
            clientSocket = NULL;
        }
    };

    QList<Node*> m_Nodelist;
    QMap<QString, MsgHandle> m_mapHandle;

    QString getOnlineUserId();
    void SendToAllOnLine(TextMessage& mmessage);

private:
    void CONN_handle(QTcpSocket* socket, TextMessage& message);
    void DSCN_handle(QTcpSocket* socket, TextMessage& message);
    void LGIN_handle(QTcpSocket* socket, TextMessage& message);
    void MSGA_handle(QTcpSocket* socket, TextMessage& message);
    void MSGP_handle(QTcpSocket* socket, TextMessage& message);
public:

    ServerHandle();
    void handle(QTcpSocket* socket, TextMessage& message);
};

#endif // SERVERHANDLE_H
