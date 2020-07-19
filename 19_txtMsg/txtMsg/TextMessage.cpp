#include "TextMessage.h"

TextMessage::TextMessage(QObject *parent) : QObject(parent)
{
    m_type = " ";
    m_data = " ";
}

TextMessage::TextMessage(QString type, QString data, QObject* parent) : QObject(parent)
{
    m_type = type.trimmed();
    m_type.resize(4, ' '); //消息类型(4字节)

    m_data = data;

}

QString TextMessage::type()
{
    return m_type;
}

QString TextMessage::data()
{
    return m_data;
}

int TextMessage::length()
{
    return m_data.length();
}

QString TextMessage::serialize()
{
    QString len =QString::asprintf("%X", m_data.length());
    len.resize(4, ' ');  //消息长度(4字节)

    return m_type + len + m_data;
}

bool TextMessage::unserialize(QString s)
{
    bool ret = s.length() >= 8;

    if(ret)
    {
        m_type = s.mid(0, 4);    //取消息类型
        int len = (s.mid(4, 4)).toInt(&ret, 16);   //取消息长度(从16进制转到10进制)
        if(ret)
        {
            m_data = s.mid(8, len);    //取消息体
        }
    }

    return ret;
}
