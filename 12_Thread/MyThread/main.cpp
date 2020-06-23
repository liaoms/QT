#include <QCoreApplication>
#include "MyThread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread th;
    th.setObjectName("thread1");
    th.setRunState(0);   //线程休眠

    th.start();

    QThread::sleep(10);
    th.setRunState(1);   //线程执行

    QThread::sleep(10);
    th.setRunState(2);      //线程退出

    th.wait();  //等待线程退出完毕(线程同步)
    qDebug() << "run here ...";

    return a.exec();
}
