#include "Widget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    init();

    testVHBoxLayout();
}

void Widget::init()
{
    this->resize(600, 400);

    m_testBtn1.setParent(this);
    m_testBtn1.setText("Btn1");
    m_testBtn1.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //横向、纵向自动延伸

    m_testBtn2.setParent(this);
    m_testBtn2.setText("Btn2");
    m_testBtn2.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_testBtn3.setParent(this);
    m_testBtn3.setText("Btn3");
    m_testBtn3.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_testBtn4.setParent(this);
    m_testBtn4.setText("Btn4");
    m_testBtn4.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Widget::testVHBoxLayout()
{
    QVBoxLayout * pVBoxLayout = new QVBoxLayout(this);
    QHBoxLayout * pHBoxLayout1 = new QHBoxLayout(this);
    QHBoxLayout * pHBoxLayout2 = new QHBoxLayout(this);

    pHBoxLayout1->setSpacing(20);   //布局内控件之间的间隔
    pHBoxLayout1->addWidget(&m_testBtn1);
    pHBoxLayout1->addWidget(&m_testBtn2);

    pHBoxLayout2->setSpacing(20);
    pHBoxLayout2->addWidget(&m_testBtn3);
    pHBoxLayout2->addWidget(&m_testBtn4);

    pVBoxLayout->setSpacing(20);
    pVBoxLayout->addLayout(pHBoxLayout1, 1);  // 两个Layout所占空间比例为1:2
    pVBoxLayout->addLayout(pHBoxLayout2, 2);

    this->setLayout(pVBoxLayout);
}

Widget::~Widget()
{

}
