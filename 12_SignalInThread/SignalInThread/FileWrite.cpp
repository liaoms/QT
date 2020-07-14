#include "FileWrite.h"

FileWrite::FileWrite(QString file, QObject *parent) : QObject(parent), m_file(file)
{
    connect(this, SIGNAL(onWrite(QString)), this, SLOT(onWriteSlot(QString)));
    connect(this, SIGNAL(onClose()), this, SLOT(onCloseSlot()));

    //将当前对象的槽函数依附到m_work线程中
    moveToThread(&m_work);
    m_work.start();
}

bool FileWrite::open()
{
    return m_file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
}

//对象调用write函数，则发送一个自定义信号，具体的写文件操作则放到线程m_work中执行，减少当前线程的IO操作，提高速率
void FileWrite::write(QString str)
{
    qDebug() << "FileWrite::write begin, tid = " << QThread::currentThreadId();
    emit onWrite(str);
    qDebug() << "FileWrite::write end, tid = " << QThread::currentThreadId();
}
void FileWrite::close()
{
    emit onClose();
}

void FileWrite::onWriteSlot(QString str)
{
    qDebug() << "FileWrite::onWriteSlot begin, tid = " << QThread::currentThreadId();
    m_file.write(str.toUtf8());
    m_file.flush();
    qDebug() << "FileWrite::onWriteSlot end, tid = " << QThread::currentThreadId();
}
void FileWrite::onCloseSlot()
{
    m_file.close();
}

FileWrite::~FileWrite()
{
    m_work.quit();   //线程退出
}
