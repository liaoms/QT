#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QAbstractSocket>
#include "TextMessage.h"
#include "TxtMsgAssembler.h"
#include "TxtMsgHandle.h"

class TCPClient : public QObject
{
    Q_OBJECT

public:
    explicit TCPClient(QObject *parent = nullptr);
    ~TCPClient();

    void connectTo(QString address, quint16 port);
    void write(TextMessage& msg);

    void close();

    void setHandle(TxtMsgHandle* handle);
private:
    QTcpSocket m_client;
    TxtMsgAssembler m_Assembler;
    TxtMsgHandle* m_pMsgHandle;


public slots:

    void onConnected();
    void onDisconnected();
    void onBytesWritten(qint64 bytes);
    void onReadyRead();


    void onError(QAbstractSocket::SocketError socketError);


};

#endif // TCPCLIENT_H
