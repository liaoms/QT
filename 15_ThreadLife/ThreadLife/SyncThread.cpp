#include "SyncThread.h"
#include <QDebug>

SyncThread::SyncThread(QObject *parent) : QThread(parent)
{

}

SyncThread::~SyncThread()
{
    wait();   //析构函数中调用wait()函数，等待线程体执行完毕后，再结束线程对象
    qDebug() << "SyncThread::~SyncThread()";
}

void SyncThread::run()
{
    for(int i=0; i<3; i++)
    {
        sleep(1);
        qDebug() << "SyncThread::run()...";
    }
}
