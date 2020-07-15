#include <QCoreApplication>
#include "TestThread.h"
#include "MyObject.h"

void testDirectConnection()
{
    static TestThread t;
    static MyObject m;
    m.moveToThread(&t);

    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()));

    t.start();

    t.wait(5 * 1000);
    t.quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testDirectConnection();

    return a.exec();
}
