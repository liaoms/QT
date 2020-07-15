#include <QCoreApplication>
#include "TestThread.h"
#include "MyObject.h"

//直接调用连接
void testDirectConnection()
{
    static TestThread t;
    static MyObject m;
    //m.moveToThread(&t); //槽函数所属线程是否为信号发送线程无关

    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()), Qt::DirectConnection);

    t.start();

    t.quit();
}

//异步调用连接( 信号发送线程必须与槽函数线程不一致)
void testQueuedConnection()
{
    static TestThread t;
    static MyObject m;
    //m.moveToThread(&t); //槽函数线程不能依附到信号发送线程

    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()), Qt::QueuedConnection);

    t.start();

    t.quit();
}

//同步调用连接( 信号发送线程必须与槽函数线程不一致)
void testBlockingQueuedConnection()
{
    static TestThread t;
    static MyObject m;
    //m.moveToThread(&t); //槽函数线程不能依附到信号发送线程

    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()), Qt::BlockingQueuedConnection);

    t.start();

    t.quit();
}

//自动调用连接
void testAutoConnection()
{
    static TestThread t;
    static MyObject m;
    //m.moveToThread(&t);   //信号线程 != 槽函数线程 ，等同于异步调用
    m.moveToThread(&t);   //信号线程 == 槽函数线程 ，等同于直接调用

    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()), Qt::AutoConnection);

    t.start();

    t.quit();
}

//唯一调用连接
void testUniqueConnection()
{
    static TestThread t;
    static MyObject m;

    //同一信号多次连接到同一个槽函数时，只有一个槽函数被调用
    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()), Qt::UniqueConnection);
    QObject::connect(&t, SIGNAL(testSignal()), &m, SLOT(testSlot()), Qt::UniqueConnection);

    t.start();

    t.quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testDirectConnection();           //直接调用，等同于直接在信号发送的地方执行槽函数
    //testQueuedConnection();           //异步调用，信号发送完毕后接着往下执行，槽函数执行情况依据槽函数依附的线程中事件队列决定
    //testBlockingQueuedConnection();   //同步调用，信号发送后，等待槽函数执行完毕再往下执行
    //testAutoConnection();             //自动调用，分信号线程与槽函数线程是否相同
    testUniqueConnection();             //唯一调用
    return a.exec();
}
