#include <QCoreApplication>
#include "testThread.h"
#include "SyncThread.h"
#include "AsynThread.h"

//线程对象的生命周期 < 线程执行周期，程序直接挂掉
void test()
{
    testThread t;
    t.start();
}

//线程同步方式，使线程对象生命周期>线程执行周期
void SyncTest()
{
    //SyncThread t;     //可在栈空间生成线程对象
    //t.start();

    SyncThread* p = new SyncThread();   //也可以在堆空间申请线程对象
    p->start();
    delete p;
}

//线程异步方式，使线程对象生命周期>线程执行周期
void AsynTest()
{
    AsynThread* p = AsynThread::NewInstance();  //只能在堆空间申请线程对象，线程体执行完后，自行申请内存释放

    p->start();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     //test();
    //SyncTest();
    AsynTest();
    return a.exec();
}
