#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDebug>

class MyThread : public QThread
{
public:
    MyThread();
    void setRunState(int state);

private:
    volatile int m_state;    //0-休眠 1-运行 2-退出

protected:
    void run();
};

#endif // MYTHREAD_H
