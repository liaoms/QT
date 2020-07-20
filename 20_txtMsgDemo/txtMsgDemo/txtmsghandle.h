#ifndef TXTMSGHANDLE_H
#define TXTMSGHANDLE_H

#include <QTcpSocket>
#include "TextMessage.h"

class TxtMsgHandle
{
public:
    virtual void handle(QTcpSocket* socket, TextMessage& message);
};

#endif // TXTMSGHANDLE_H
