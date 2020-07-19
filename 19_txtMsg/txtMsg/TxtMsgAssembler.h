#ifndef TXTMSGASSEMBLER_H
#define TXTMSGASSEMBLER_H

#include <QObject>
#include <QQueue>
#include <QSharedPointer>
#include "TextMessage.h"

// 从字节流装配文本协议对象 类
class TxtMsgAssembler : public QObject
{
    Q_OBJECT

private:
    QString m_type;
    QString m_data;
    int m_length;

    QQueue<char> m_MsgQueue;   //保存接收的数据流，消息类型、长度，消息体，都依次从里边取

public:
    TxtMsgAssembler(QObject *parent = nullptr);
    void prepare(const char* msg, int len);
    void makeTypeAndLength();    // 获取消息头
    TextMessage* makeMessage();  //获取消息体
    QSharedPointer<TextMessage> assemble (const char* msg, int len);   //返回消息类对象指针
    QSharedPointer<TextMessage> assemble ();
    void reset();
};

#endif // TXTMSGASSEMBLER_H
