#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QListView>
#include <QTableView>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QStandardItemModel m_itemModel;

    QTreeView m_treeView;
    QTableView m_tableView;
    QListView m_listView;

    void initUI();
    void initModel();

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // __WIDGET_H__
