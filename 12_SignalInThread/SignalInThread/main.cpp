#include <QCoreApplication>
#include "TestThread.h"
#include "MyObject.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main tid = " << QThread::currentThreadId();

    TestThread t;   //线程t中槽函数的依附线程默认为主线程(main线程)
    MyObject m;     //同上(即槽函数实际运行位置main线程中)

    //线程信号对应的槽函数，应该运行在对应线程的栈中，运行到其他线程中，临界资源访问可能出错
    m.moveToThread(&t);     //将m中槽函数的依附线程设置为线程t
    t.moveToThread(&t);     //将线程t中槽函数的依附线程设置为线程t

    QObject::connect(&t, SIGNAL(started()), &m, SLOT(threadStartSlot()));   //关联线程started()信号
    QObject::connect(&t, SIGNAL(finished()), &m, SLOT(threadFinishSlot())); //关联线程finished()信号

    t.start();
    return a.exec();
}
