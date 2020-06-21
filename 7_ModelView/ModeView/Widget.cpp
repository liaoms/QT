#include "Widget.h"
#include <QGridLayout>
#include <QDir>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_treeView(this)
{
    resize(600, 400);
    initUI();

    m_fsModel.setRootPath("E:/");       //设置文件模型根目录
    m_treeView.setModel(&m_fsModel);    //关联视图与模型
    m_treeView.setRootIndex(m_fsModel.index("E:/"));   //设置视图显示的根索引

    connect(&m_treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onClicked(QModelIndex)));

}

void Widget::initUI()
{
    QGridLayout *Layout = new QGridLayout();

    Layout->addWidget(&m_treeView, 0, 0, 1, 1);

    setLayout(Layout);
}

//获取选中的文件
void Widget::onClicked(const QModelIndex &index)
{
    qDebug() << m_fsModel.filePath(index);
}

Widget::~Widget()
{

}
