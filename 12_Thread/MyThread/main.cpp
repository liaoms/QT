#include <QCoreApplication>
#include "MyThread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread th1;
    th1.setObjectName("thread1");
    MyThread th2;
    th2.setObjectName("thread2");

    th1.setRunState(0);   //线程休眠
    th2.setRunState(0);   //线程休眠

    th1.start();
    th2.start();

    QThread::sleep(10);
    th1.setRunState(1);   //线程执行
    th2.setRunState(1);   //线程执行

    QThread::sleep(10);
    th1.setRunState(2);      //线程退出
    th2.setRunState(2);      //线程退出

    th1.wait();  //等待线程退出完毕(线程同步)
    th2.wait();  //等待线程退出完毕(线程同步)
    qDebug() << "run here ...";

    return a.exec();
}
