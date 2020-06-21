#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>

class Widget : public QWidget
{
    Q_OBJECT

protected:
    bool event(QEvent *event);              //重写总事件处理函数
    void keyPressEvent(QKeyEvent *event);   //重写按键按下事件处理函数

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
