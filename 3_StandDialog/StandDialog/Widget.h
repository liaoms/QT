#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton SimpleMsgBtn;
    QPushButton CustomMsgBtn;
    QPushButton OpenFileBtn;
    QPushButton SaveFileBtn;
    QPushButton ColorBtn;
    QPushButton InputBtn;
private slots:
    void SimpleMsgBtn_Clicked();
    void CustomMsgBtn_Clicked();
    void OpenFileBtn_Clicked();
    void SaveFileBtn_Clicked();
    void ColorBtn_Clicked();
    void InputBtn_Clicked();
public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif
