#ifndef __TESTSIGNAL_H__
#define __TESTSIGNAL_H__

#include <QObject>

class TestSignal : public QObject
{
    Q_OBJECT

signals:
    void mySignal(int i);   //子定义信号

public:
    void send(int i)
    {
        emit mySignal(i);   //使用emit发送信号
    }
};

#endif // __TESTSIGNAL_H__
