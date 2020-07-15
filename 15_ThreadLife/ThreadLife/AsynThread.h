#ifndef ASYNTHREAD_H
#define ASYNTHREAD_H

#include <QThread>

class AsynThread : public QThread
{
    Q_OBJECT
protected:
    explicit AsynThread(QObject *parent = nullptr);
    ~AsynThread();
protected:
    void run();

public:
    static AsynThread* NewInstance();
};

#endif // ASYNTHREAD_H
