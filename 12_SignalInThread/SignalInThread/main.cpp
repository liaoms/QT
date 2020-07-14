#include <QCoreApplication>
#include "TestThread.h"
#include "MyObject.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main tid = " << QThread::currentThreadId();

    TestThread t;
    MyObject m;

    QObject::connect(&t, SIGNAL(started()), &m, SLOT(threadStartSlot()));   //关联线程started()信号
    QObject::connect(&t, SIGNAL(finished()), &m, SLOT(threadFinishSlot())); //关联线程finished()信号

    t.start();
    return a.exec();
}
