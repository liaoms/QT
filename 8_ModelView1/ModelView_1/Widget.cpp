#include "Widget.h"
#include <QVBoxLayout>


Widget::Widget(QWidget *parent) : QWidget(parent), m_treeView(this), m_tableView(this), m_listView(this)
{
    resize(600, 500);
    initUI();
    initModel();

    m_treeView.setModel(&m_itemModel);   //同一个模型，设置到不同视图中
    m_listView.setModel(&m_itemModel);
    m_tableView.setModel(&m_itemModel);

}

void Widget::initUI()
{
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(&m_tableView);
    layout->addWidget(&m_treeView);
    layout->addWidget(&m_listView);

    setLayout(layout);
}

void Widget::initModel()
{
    QStandardItem * root = m_itemModel.invisibleRootItem();   //从模型中获取一个虚拟根节点

    QStandardItem * ItemA = new QStandardItem();
    ItemA->setData("A", Qt::DisplayRole);       //设置属性角色
    ItemA->setData("Tip A", Qt::ToolTipRole);

    QStandardItem * ItemB = new QStandardItem();
    ItemB->setData("B", Qt::DisplayRole);
    ItemB->setData("Tip B", Qt::ToolTipRole);

    QStandardItem * ItemC = new QStandardItem();
    ItemC->setData("C", Qt::DisplayRole);
    ItemC->setData("Tip C", Qt::ToolTipRole);

    QStandardItem * ItemD = new QStandardItem();
    ItemD->setData("D", Qt::DisplayRole);
    ItemD->setData("Tip D", Qt::ToolTipRole);

    root->setChild(0, 0, ItemA);    //root节点设置子节点ItemA，位置为0行0列处，一下类似
    root->setChild(0, 1, ItemB);    //同上
    ItemA->setChild(0,0, ItemC);
    ItemC->setChild(0,0, ItemD);
}

Widget::~Widget()
{

}
