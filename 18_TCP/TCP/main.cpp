#include <QCoreApplication>
#include "TCPClient.h"
#include "TCPServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if 0
    TCPClient t;
    t.connectTo("127.0.0.1", 8080);
    t.write("hello tcp...");

    t.close();
#endif

    TCPServer t;
    t.start(8080);

    return a.exec();
}
