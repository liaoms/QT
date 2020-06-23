#include "MyThread.h"

int MyThread::m_value = 0;
QMutex MyThread::m_mutex;

MyThread::MyThread()
{
    m_state = 0;
}

void MyThread::setRunState(int state)
{
    m_state = state;
}

void MyThread::run()
{
    qDebug() << this->objectName() << "is begin";
    while(1)
    {
        if(0 == m_state)
        {

            qDebug() << this->objectName() << "is sleep...";
            sleep(1);
            continue;
        }
        else if(2 == m_state)
        {
            qDebug() << this->objectName() << "is finish...";
            break;
        }

        m_mutex.lock();
        m_value ++;
        qDebug() << this->objectName() << " m_value = " << m_value;
        m_mutex.unlock();
        //sleep(1);
    }
}
