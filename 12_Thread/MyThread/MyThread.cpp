#include "MyThread.h"

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

        qDebug() << this->objectName() << "is runing...";
        sleep(1);
    }
}
