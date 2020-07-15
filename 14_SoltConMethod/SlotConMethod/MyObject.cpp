#include "MyObject.h"
#include <QDebug>

MyObject::MyObject(QObject *parent) : QObject(parent)
{

}

void MyObject::testSlot()
{
    qDebug() << "MyObject::testSlot()";
}
