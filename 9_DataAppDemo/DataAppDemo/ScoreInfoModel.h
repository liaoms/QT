
//数据组织层

#ifndef __SCOREINFOMODEL_H__
#define __SCOREINFOMODEL_H__

#include <QObject>
#include <QStandardItem>
#include <QTableView>
#include <QList>
#include "ScoreInfo.h"

class ScoreInfoModel : public QObject
{
    Q_OBJECT

    QStandardItemModel m_model;
public:
    explicit ScoreInfoModel(QObject *parent = 0);
    bool add(ScoreInfo info);
    bool add(QList<ScoreInfo> list);
    bool remove(int i);
    ScoreInfo getItem(int i);
    int count();
    void clear();
    void setView(QTableView& view);
};

#endif // __SCOREINFOMODEL_H__
