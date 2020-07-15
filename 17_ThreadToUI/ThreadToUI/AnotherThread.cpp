#include "AnotherThread.h"
#include <QDebug>

AnotherThread::AnotherThread(QObject *parent) : QObject(parent)
{
    moveToThread(&m_work);  //将当前对象的线程依附调整到线程成员对象上
    connect(&m_work, SIGNAL(started()), this, SLOT(tMain()));   //关联线程成员对象started()信号到自定义的线程函数入口
}

AnotherThread::~AnotherThread()
{
    m_work.wait(); //线程同步，等待线程执行完毕后退出
    qDebug() << "AnotherThread::~AnotherThread()...";
}

void AnotherThread::start()
{
    m_work.start();
}
void AnotherThread::exit()
{
    m_work.exit();
}

//自定义的线程入口函数
void AnotherThread::tMain()
{
    //emit UpdateUI("begin");  //发送自定信号给UI
    for(int i=1; i<=100; i++)
    {
        QThread::sleep(1);
        emit UpdateUI(QString::number(i));
    }
    //emit UpdateUI("end");
    m_work.quit();  //结束线程内部时间循环(重要点)
}
