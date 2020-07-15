#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QThread>

class SyncThread : public QThread
{
    Q_OBJECT
public:
    explicit SyncThread(QObject *parent = nullptr);
    ~SyncThread();
protected:
    void run();
};

#endif // SYNCTHREAD_H
