#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>


class TestThread : public QThread
{
Q_OBJECT
public:
    TestThread(QObject* parent = nullptr);

protected:
    void run();

signals:
    void testsignal();   //线程内自定义信号

private slots:
    void testSlot();    //线程内槽函数

};

#endif // TESTTHREAD_H
