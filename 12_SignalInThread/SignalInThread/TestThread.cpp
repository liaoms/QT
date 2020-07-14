#include "TestThread.h"
#include <QDebug>

TestThread::TestThread(QObject* parent) : QThread(parent)
{

    connect(this, SIGNAL(testsignal()), this, SLOT(testSlot()));
}

void TestThread::run()
{
    qDebug() << " thread begin";
    qDebug() << "TestThread tid = " << currentThreadId();
    int i=5;
    while(i--)
    {
        qDebug() << " thread run...";
        sleep(1);
    }
    emit testsignal();

    this->exec();
    qDebug() << " thread end";
}


void TestThread::testSlot()
{
    qDebug() << "testSlot tid = " << currentThreadId();
    qDebug() << "TestThread::testSlot()";
}
