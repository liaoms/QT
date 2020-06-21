#include "MyLineEdit.h"
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

bool MyLineEdit::event(QEvent* event)
{
    if(QEvent::KeyPress == event->type())
    {
        qDebug() << "MyLineEdit::event";
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
