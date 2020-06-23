#include "Widget.h"
#include <QModelIndex>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    resize(550, 200);
    //setFixedSize(320, 120);
    initUI();
    initView();
    initModel();

    m_view.setModel(&m_model);

    m_testBtn.setParent(this);
    m_testBtn.move(10, 120);
    m_testBtn.resize(500, 100);
    m_testBtn.setText("Test");

    connect(&m_testBtn, SIGNAL(clicked()), this, SLOT(onTestBtnClicked()));
}

void Widget::initUI()
{
    QVBoxLayout* vLayout = new QVBoxLayout();

    vLayout->addWidget(&m_view, 5);
    vLayout->addWidget(&m_testBtn, 1);

    setLayout(vLayout);
}

void Widget::initView()
{
    m_view.setParent(this);
    m_view.move(10, 10);
    m_view.resize(300, 100);
    m_view.setItemDelegate(&m_delegate);   //视图设置自定义委托
}

void Widget::initModel()
{
    QStandardItem* root = m_model.invisibleRootItem();
    QStringList hl;
    QStandardItem* itemA1 = new QStandardItem();
    QStandardItem* itemB1 = new QStandardItem();
    QStandardItem* itemC1 = new QStandardItem();
    QStandardItem* itemA2 = new QStandardItem();
    QStandardItem* itemB2 = new QStandardItem();
    QStandardItem* itemC2 = new QStandardItem();

    hl.append("Language");
    hl.append("Level");
    hl.append("Script");

    m_model.setHorizontalHeaderLabels(hl);

    itemA1->setData("Delphi", Qt::DisplayRole);
    itemB1->setData(QChar('A'), Qt::DisplayRole);
    itemC1->setData(false, Qt::DisplayRole);

    itemA2->setData("Perl", Qt::DisplayRole);
    itemB2->setData(QChar('B'), Qt::DisplayRole);
    itemC2->setData(true, Qt::DisplayRole);

    root->setChild(0, 0, itemA1);
    root->setChild(0, 1, itemB1);
    root->setChild(0, 2, itemC1);
    root->setChild(1, 0, itemA2);
    root->setChild(1, 1, itemB2);
    root->setChild(1, 2, itemC2);
}

void Widget::onTestBtnClicked()
{
    qDebug() << "Model Data:";

    for(int i=0; i<m_model.rowCount(); i++)
    {
        qDebug() << "Row: " << i;
        for(int j=0; j<m_model.columnCount(); j++)
        {
            QModelIndex index = m_model.index(i, j, QModelIndex());
            QString text = index.data(Qt::DisplayRole).toString();

            qDebug() << text;
        }
        qDebug() << endl;
    }

    qDebug() << "Current View Delegate: " << m_view.itemDelegate();   //获取视图当前使用的委托
}

Widget::~Widget()
{
    
}
