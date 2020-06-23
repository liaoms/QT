#include <QCoreApplication>
#include <QObject>
#include "TestSignal.h"
#include "RxObject.h"

//多个信号发送一个槽函数
void multi_to_one()
{
    TestSignal sig1;
    sig1.setObjectName("sig1");

    TestSignal sig2;
    sig2.setObjectName("sig2");

    RxObject rx;
    rx.setObjectName("rx");

    QObject::connect(&sig1, SIGNAL(mySignal(int)), &rx, SLOT(myslot(int)));
    QObject::connect(&sig2, SIGNAL(mySignal(int)), &rx, SLOT(myslot(int)));

    sig1.send(1);
    sig2.send(2);
}

//一个信号发送多个槽函数
void one_to_multi()
{
    TestSignal sig1;
    sig1.setObjectName("sig1");

    RxObject rx1;
    rx1.setObjectName("rx1");

    RxObject rx2;
    rx2.setObjectName("rx2");

    QObject::connect(&sig1, SIGNAL(mySignal(int)), &rx1, SLOT(myslot(int)));
    QObject::connect(&sig1, SIGNAL(mySignal(int)), &rx2, SLOT(myslot(int)));

    sig1.send(1);
}

//信号发送到信号
void signal_to_signal()
{
    TestSignal sig1;
    sig1.setObjectName("sig1");

    TestSignal sig2;
    sig2.setObjectName("sig2");

    RxObject rx;
    rx.setObjectName("rx");

    QObject::connect(&sig1, SIGNAL(mySignal(int)), &sig2, SIGNAL(mySignal(int)));   //信号发到信号
    QObject::connect(&sig2, SIGNAL(mySignal(int)), &rx, SLOT(myslot(int)));

    sig1.send(1);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //multi_to_one();
    //one_to_multi();
    signal_to_signal();

    return a.exec();
}


