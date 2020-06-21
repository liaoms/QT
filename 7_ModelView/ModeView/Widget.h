#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QFileSystemModel m_fsModel;
    QTreeView m_treeView;

    void initUI();

private slots:
    void onClicked(const QModelIndex &index);

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
