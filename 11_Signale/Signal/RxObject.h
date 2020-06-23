#ifndef __RXOBJECT_H__
#define __RXOBJECT_H__

#include <QObject>
#include <QDebug>

class RxObject : public QObject
{
    Q_OBJECT
public:

protected slots:
    void myslot(int i)
    {
        qDebug() << "sender()->objectName() = " << sender()->objectName();
        qDebug() << "recive()->objectName() = " << this->objectName();
        qDebug() << "value = " << i;
    }
};

#endif // RXOBJECT_H
