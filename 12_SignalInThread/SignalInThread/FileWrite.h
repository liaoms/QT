#ifndef FILEWRITE_H
#define FILEWRITE_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QString>
#include <QDebug>

class FileWrite : public QObject
{
    Q_OBJECT

private:
    class work : public QThread
    {
    protected:
        void run()
        {
            qDebug() << "work begin, tid = " << QThread::currentThreadId();
            this->exec();   //需要开启事件循环，才回处理依附到该线程内的槽函数
        }
    };

    work m_work;
    QFile m_file;

public:
    FileWrite(QString file, QObject *parent = nullptr);
    ~FileWrite();

    bool open();
    void write(QString str);
    void close();

signals:
    void onWrite(QString str);
    void onClose();

private slots:
    void onWriteSlot(QString str);
    void onCloseSlot();
};

#endif // FILEWRITE_H
