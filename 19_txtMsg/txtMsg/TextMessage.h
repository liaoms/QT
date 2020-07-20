#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>
#include <QString>
#include <QByteArray>

//文本协议设计：消息类型(4字节) + 消息长度(4字节) + 消息体

class TextMessage : public QObject
{
    Q_OBJECT

private:
    QString m_data;
    QString m_type;

public:
    TextMessage(QObject *parent = nullptr);
    TextMessage(QString type, QString data, QObject* parent = nullptr);

public:
    QString type();
    QString data();
    int length();

    QByteArray serialize();   //序列化
    bool unserialize(QByteArray s);    //反序列化

};

#endif // TEXTMESSAGE_H
