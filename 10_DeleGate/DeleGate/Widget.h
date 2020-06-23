#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include "CustomizedItemDelegate.h"

class Widget : public QWidget
{
    Q_OBJECT
    
    QTableView m_view;
    QStandardItemModel m_model;
    QPushButton m_testBtn;
    CustomizedItemDelegate m_delegate;

    void initUI();
    void initView();
    void initModel();

private slots:
    void onTestBtnClicked();
public:
    Widget(QWidget* parent = 0);
    ~Widget();
};

#endif // __WIDGET_H__
