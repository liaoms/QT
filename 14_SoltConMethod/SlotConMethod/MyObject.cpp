#include "MyObject.h"
#include <QDebug>
#include <QThread>

MyObject::MyObject(QObject *parent) : QObject(parent)
{

}

void MyObject::testSlot()
{
    QThread::sleep(3);
    qDebug() << "MyObject::testSlot()";

}
