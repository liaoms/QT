#include "TestThread.h"
#include <QDebug>

TestThread::TestThread(QObject *parent) : QThread(parent)
{

}

void TestThread::run()
{
    qDebug() << "TestThread::run() begin ...";
    for(int i=0; i<3; i++)
    {
        qDebug() << "TestThread::run()...";
        sleep(1);
    }

    emit testSignal();
    qDebug() << "TestThread::run() emit end ...";

    this->exec();
    qDebug() << "TestThread::run() end ...";
}
