#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
public:
    MyObject(QObject *parent = nullptr);


public slots:
    void threadStartSlot();
    void threadFinishSlot();

};

#endif // MYOBJECT_H
