#include "TextMessage.h"

TextMessage::TextMessage(QObject *parent) : QObject(parent)
{
    m_type.clear();
    m_data.clear();
}

TextMessage::TextMessage(QString type, QString data, QObject* parent) : QObject(parent)
{
    m_type = type.trimmed();
    m_type.resize(4, ' '); //消息类型(4字节)

    m_data = data.mid(0, 15000);

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
    return (m_data.toUtf8()).length();
}

QByteArray TextMessage::serialize()
{
    QByteArray ret;

    QByteArray ba = m_data.toUtf8();

    QString len =QString::asprintf("%X", ba.length());
    len.resize(4, ' ');  //消息长度(4字节)

    ret.append(m_type.toStdString().c_str(), 4);
    ret.append(len.toStdString().c_str(), 4);
    ret.append(ba);

    return ret;
}

bool TextMessage::unserialize(QByteArray s)
{
    bool ret = s.length() >= 8;

    if(ret)
    {
        m_type = QString(s.mid(0, 4));    //取消息类型
        int len = (s.mid(4, 4)).toInt(&ret, 16);   //取消息长度(从16进制转到10进制)

        ret = ret && ( (s.length()-8) == len );
        if(ret)
        {
            m_data = QString(s.mid(8, len));    //取消息体
        }
    }

    return ret;
}
