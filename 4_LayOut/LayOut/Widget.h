#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QPushButton m_testBtn1;
    QPushButton m_testBtn2;
    QPushButton m_testBtn3;
    QPushButton m_testBtn4;
    QPushButton m_testBtn5;
    QPushButton m_testBtn6;

public:
    Widget(QWidget *parent = 0);

    void init();

    void testVHBoxLayout();
    void testGridLayout();

    ~Widget();
};

#endif // WIDGET_H
