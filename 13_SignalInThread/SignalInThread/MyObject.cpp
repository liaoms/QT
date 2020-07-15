#include "MyObject.h"
#include <QDebug>
#include <QThread>

MyObject::MyObject(QObject *parent) : QObject(parent)
{

}

void MyObject::threadStartSlot()
{
    qDebug() << "MyObject::threadStartSlot()" << "MyObject tid = " << QThread::currentThreadId();
}
void MyObject::threadFinishSlot()
{
    qDebug() << "MyObject::threadFinishSlot()" << "MyObject tid = " << QThread::currentThreadId();
}
