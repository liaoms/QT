#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QAbstractSocket>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = nullptr);
    ~TCPClient();

    void connectTo(QString address, quint16 port);
    void write(QString str);

    void close();
private:
    QTcpSocket m_client;

public slots:

    void onConnected();
    void onDisconnected();
    void onBytesWritten(qint64 bytes);
    void onReadyRead();


    void onError(QAbstractSocket::SocketError socketError);


};

#endif // TCPCLIENT_H
