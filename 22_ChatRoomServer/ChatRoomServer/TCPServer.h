#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include "TextMessage.h"
#include "TxtMsgAssembler.h"
#include "TxtMsgHandle.h"

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();

    void start(int port);
    void stop();

    void setHandle(TxtMsgHandle* handle);

private:
    QTcpServer m_server;
    QMap<QTcpSocket*, TxtMsgAssembler*> m_map;

    //TxtMsgAssembler m_Assembler;
    TxtMsgHandle* m_pMsgHandle;

protected slots:

    //服务端槽函数
    void onNewConnection();
    void onAcceptError(QAbstractSocket::SocketError socketError);

    //新链接的客户端的槽函数
    void onConnected();
    void onDisconnected();
    void onBytesWritten(qint64 bytes);
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

};

#endif // TCPSERVER_H
