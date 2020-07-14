#include <QCoreApplication>
#include "TestThread.h"
#include "MyObject.h"
#include "FileWrite.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main tid = " << QThread::currentThreadId();

    FileWrite f("test.txt");

    if(f.open())
    {
        f.write("aaaaa");
        f.write("直到世界尽头");
        f.close();
    }

    return a.exec();
}
