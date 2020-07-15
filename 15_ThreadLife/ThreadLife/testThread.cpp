#include "testThread.h"

testThread::testThread(QObject* parent) : QThread(parent)
{

}

void testThread::run()
{
    for(int i=0; i<3; i++)
    {
        sleep(1);
    }
}
