#include <QCoreApplication>
#include "AnotherThread.h"

void testAnotherThread()
{
    AnotherThread t;
    t.start();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testAnotherThread();

    return a.exec();
}
