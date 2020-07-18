#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();

    void start(int port);
    void stop();

private:
    QTcpServer m_server;
    QList<QTcpSocket*> m_ClienList;

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
