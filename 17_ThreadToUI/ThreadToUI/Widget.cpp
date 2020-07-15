#include "Widget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    connect(&m_thread, SIGNAL(UpdateUI(QString)), this, SLOT(onUpdateUI(QString)));   //关联线程对象的自定义信号到UI线程的更新槽函数

    m_thread.start();
}

void Widget::initUI()
{
    m_textEdit.setParent(this);

    m_progressBar.setParent(this);
    m_progressBar.setMaximum(100);
    m_progressBar.setMinimum(0);
    m_progressBar.setValue(20);

    QVBoxLayout* pLayout = new QVBoxLayout();

    pLayout->addWidget(&m_textEdit,5);
    pLayout->addWidget(&m_progressBar, 1);

    this->setLayout(pLayout);
}

void Widget::onUpdateUI(QString str)
{
    m_textEdit.appendPlainText(str);
    m_progressBar.setValue(str.toInt());
}

Widget::~Widget()
{

}
