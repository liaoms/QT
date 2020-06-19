#include "Widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    init();

    //testVHBoxLayout();
    //testGridLayout();
    testFormLayout();
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

    m_testBtn5.setParent(this);
    m_testBtn5.setText("Btn5");
    m_testBtn5.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_testBtn6.setParent(this);
    m_testBtn6.setText("Btn6");
    m_testBtn6.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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

void Widget::testGridLayout()
{
    QGridLayout* pGLayout = new QGridLayout(this);
    QVBoxLayout* pVBLayout = new QVBoxLayout(this);

    pVBLayout->addWidget(&m_testBtn4);
    pVBLayout->addWidget(&m_testBtn5);
    pVBLayout->addWidget(&m_testBtn6);

    pGLayout->setSpacing(20);
    pGLayout->addWidget(&m_testBtn1, 0, 0);  //所处位置：第0行 第0列
    pGLayout->addWidget(&m_testBtn2, 0, 1);
    pGLayout->addWidget(&m_testBtn3, 1, 0);
    pGLayout->addLayout(pVBLayout, 1, 1);

    pGLayout->setRowStretch(0, 1);  //设置比例系数
    pGLayout->setRowStretch(1, 2);
    pGLayout->setColumnStretch(0, 1);
    pGLayout->setColumnStretch(1, 2);

    this->setLayout(pGLayout);
}

void Widget::testFormLayout()
{
    QFormLayout *pFLayout = new QFormLayout(this);
    QVBoxLayout *pVBlayout = new QVBoxLayout(this);

    pVBlayout->addWidget(&m_testBtn4);
    pVBlayout->addWidget(&m_testBtn5);
    pVBlayout->addWidget(&m_testBtn6);

    pFLayout->addRow("lable1", &m_testBtn1);
    pFLayout->addRow("lable2", &m_testBtn2);
    pFLayout->addRow("lable3", &m_testBtn3);

    pFLayout->addRow("lable4", pVBlayout);

    pFLayout->setFormAlignment(Qt::AlignCenter);
    pFLayout->setLabelAlignment(Qt::AlignVCenter);
    //pFLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    setLayout(pFLayout);

}

Widget::~Widget()
{

}
