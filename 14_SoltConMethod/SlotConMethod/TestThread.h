#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>


class TestThread : public QThread
{
    Q_OBJECT
public:
    TestThread(QObject *parent = nullptr);

protected:
    void run();

signals:
    void testSignal();

public slots:

};

#endif // TESTTHREAD_H
