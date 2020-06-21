#ifndef __STRINGEVENT_H__
#define __STRINGEVENT_H__

#include <QEvent>
#include <QString>

//自定义一个事件
class StringEvent : public QEvent
{
private:
    QString m_data;

public:
    const static Type strTYPE = static_cast<Type>(QEvent::User + 0x01);  //事件类型必须唯一
    StringEvent(QString data, Type type = strTYPE);


    QString data();

};

#endif // __STRINGEVENT_H__
