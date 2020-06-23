#include <QCoreApplication>
#include "MyThread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread th;
    th.setObjectName("thread1");
    th.setRunState(0);

    th.start();

    QThread::sleep(10);
    th.setRunState(1);


    QThread::sleep(10);
    th.setRunState(2);

    return a.exec();
}
