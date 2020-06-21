#include "Widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

}

//按键按下事件先经过总事件处理函数，再经过按键按下事件处理函数
bool Widget::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        qDebug() << "Widget::event";
    }

    return QWidget::event(event);   //直接调用父类默认事件处理函数
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Widget::keyPressEvent";

    QWidget::keyPressEvent(event);  //直接调用父类默认事件处理函数
}

Widget::~Widget()
{

}
