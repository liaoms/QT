
//数据表示层

#ifndef __SCOREINFO_H__
#define __SCOREINFO_H__

#include <QObject>

class ScoreInfo : public QObject
{
    Q_OBJECT

    QString m_id;
    QString m_name;
    int m_score;
public:
    ScoreInfo(QObject* parent = 0);
    ScoreInfo(QString id, QString name, int score, QObject* parent = 0);
    ScoreInfo(const ScoreInfo& obj);
    ScoreInfo& operator= (const ScoreInfo& obj);
    QString id();
    QString name();
    int score();
    
};

#endif // __SCOREINFO_H__
