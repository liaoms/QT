#ifndef TXTMSGHANDLE_H
#define TXTMSGHANDLE_H

#include <QTcpSocket>
#include "TextMessage.h"

class TxtMsgHandle
{
public:
    virtual void handle(QTcpSocket* socket, TextMessage& message) = 0;
};

#endif // TXTMSGHANDLE_H
