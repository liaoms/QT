#include "ServerHandle.h"

void ServerHandle::handle(QTcpSocket* socket, TextMessage& message)
{
    qDebug() << socket;
    qDebug() << message.type();
    qDebug() << message.data();

    if("CONN" == message.type())
    {

    }
    else if("DSCN" == message.type())
    {

    }
}
