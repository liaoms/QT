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
    volatile int m_state;    //0-暂停 1-运行 2-休眠

protected:
    void run();
};

#endif // MYTHREAD_H
