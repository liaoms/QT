#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>

class testThread : public QThread
{
    Q_OBJECT
public:
    testThread(QObject* parent = nullptr);

protected:
    void run();
};

#endif // TESTTHREAD_H
