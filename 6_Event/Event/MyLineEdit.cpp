#include "MyLineEdit.h"
#include <QDebug>
#include "StringEvent.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

bool MyLineEdit::event(QEvent* event)
{
    if(QEvent::KeyPress == event->type())
    {
        qDebug() << "MyLineEdit::event";
    }
    else if(StringEvent::strTYPE == event->type())   //发送事件的目标对象中也可对发送的事件进行处理
    {
        qDebug() << "StringEvent::strTYPE == event->type()";
    }

    return QLineEdit::event(event);
}

void MyLineEdit::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "MyLineEdit::keyPressEvent";

    QLineEdit::keyPressEvent(event);

    //event->accept();   //接收事件，事件不会传往父组件
    //event->ignore();    //忽略事件，事件会传往父组件
}
