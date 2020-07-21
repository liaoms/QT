#ifndef SERVERHANDLE_H
#define SERVERHANDLE_H

#include "TxtMsgHandle.h"
#include "TextMessage.h"
#include <QTcpSocket>
#include <QList>

class ServerHandle : public TxtMsgHandle
{
private:
    struct Node
    {
        QString id;
        QString pwd;
        QTcpSocket* clientSocket;
    };

    QList<Node> m_Nodelist;

public:
    void handle(QTcpSocket* socket, TextMessage& message);
};

#endif // SERVERHANDLE_H
