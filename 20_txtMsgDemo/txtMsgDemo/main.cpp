#include <QCoreApplication>
#include "TxtMsgHandle.h"
#include "TCPClient.h"
#include "TCPServer.h"

class Handle : public TxtMsgHandle
{
public:
    void handle(QTcpSocket* socket, TextMessage& message)
    {
        qDebug() << endl << (socket->peerAddress()).toString() << ":" << socket->peerPort();
        qDebug() << "type = " << message.type();
        qDebug() << "length = " << message.length();
        qDebug() << "data = " << message.data() << endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Handle handle;
    TextMessage message("Demo", "Delphi Tang 狄泰软件学院！");
    TextMessage message1("Demo", "LMS 努力，奋斗");

    TCPServer server;
    TCPClient client;
    TCPClient client1;

    server.setHandle(&handle);
    server.start(8080);


    client.setHandle(&handle);
    client.connectTo("127.0.0.1", 8080);

    client1.setHandle(&handle);
    client1.connectTo("127.0.0.1", 8080);

    client.write(message);
    client1.write(message1);

    return a.exec();
}
