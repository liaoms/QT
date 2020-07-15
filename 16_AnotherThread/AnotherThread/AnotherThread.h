#ifndef ANOTHERTHREAD_H
#define ANOTHERTHREAD_H

#include <QThread>

//另一种创建线程方式思路:
// 1、包含QThread成员对象，将成员对象的started()信号连接到一个自定义的函数
// 2、将当前对象的线程依附调整到线程成员对象上
class AnotherThread : public QObject
{
    Q_OBJECT
private:
    QThread m_work;
public:
    explicit AnotherThread(QObject *parent = nullptr);
    ~AnotherThread();

    void start();
    void exit();

protected slots:
    void tMain();   //自定义线程入口函数
};

#endif // ANOTHERTHREAD_H
