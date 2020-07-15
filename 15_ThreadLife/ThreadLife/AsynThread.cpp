#include "AsynThread.h"
#include <QDebug>

AsynThread::AsynThread(QObject *parent) : QThread(parent)
{

}

AsynThread::~AsynThread()
{
    qDebug() << "AsynThread::~AsynThread()";
}

void AsynThread::run()
{
    for(int i=0; i<3; i++)
    {
        sleep(1);
        qDebug() << "AsynThread::run()...";
    }

    deleteLater();   //线程体执行完成后自行申请内存释放
}


AsynThread* AsynThread::NewInstance()
{
    return new AsynThread();
}
