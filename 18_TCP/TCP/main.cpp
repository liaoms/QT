#include <QCoreApplication>
#include "TCPClient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TCPClient t;
    t.connectTo("127.0.0.1", 8080);
    t.write("hello tcp...");

    t.close();

    return a.exec();
}
