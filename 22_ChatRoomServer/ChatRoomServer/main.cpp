#include <QCoreApplication>
#include "TCPServer.h"
#include "ServerHandle.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerHandle hander;
    TCPServer server;
    server.setHandle(&hander);

    server.start(8080);

    return a.exec();
}
