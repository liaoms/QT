#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QPushButton>
#include "MyLineEdit.h"
#include "StringEvent.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    MyLineEdit m_lineEdit;
    MyLineEdit m_lineEdit1;
    MyLineEdit m_lineEdit2;

    QPushButton m_delBtn;
    QPushButton m_delBtn1;
    QPushButton m_delBtn2;

    void initUI();

private slots:
    void ondelBtnClicked();
    void ondelBtn1Clicked();
    void ondelBtn2Clicked();

protected:
    bool event(QEvent *event);              //重写总事件处理函数
    void keyPressEvent(QKeyEvent *event);   //重写按键按下事件处理函数

    bool eventFilter(QObject *watched, QEvent *event);  //重写事件过滤器

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
