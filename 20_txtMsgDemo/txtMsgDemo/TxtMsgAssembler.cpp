#include "TxtMsgAssembler.h"

TxtMsgAssembler::TxtMsgAssembler(QObject *parent) : QObject(parent)
{
    m_MsgQueue.clear();
    reset();
}

void TxtMsgAssembler::prepare(const char* msg, int len)
{
    for(int i=0; i<len; i++)
    {
        m_MsgQueue.append(msg[i]);
    }
}

QByteArray TxtMsgAssembler::fetch(int n)
{
    QByteArray ret;

    for(int i=0; i<n; i++)
    {
        ret.append(m_MsgQueue.dequeue());
    }

    return ret;
}

bool TxtMsgAssembler::makeTypeAndLength()
{
    bool ret = m_MsgQueue.length() > 8;
    if(ret)
    {
        QString len = "";

        m_type = QString(fetch(4));

        len = QString(fetch(4));

        bool ret =true;
        m_length = len.toInt(&ret, 16);

        if(!ret)
        {
            reset();
        }
    }

    return ret;
}

TextMessage* TxtMsgAssembler::makeMessage()
{
    TextMessage* ret = NULL;
    int Len = (m_length - m_data.length()) < m_MsgQueue.length() ? m_length : m_MsgQueue.length();

    m_data = fetch(Len);

    if((m_data.length() == m_length) && (m_length > 0))
    {
        ret = new TextMessage(m_type, QString(m_data));

        if(NULL != ret)
        {
            reset();
        }
    }

    return ret;
}

QSharedPointer<TextMessage> TxtMsgAssembler::assemble (const char* msg, int len)
{
    prepare(msg, len);

    return assemble();
}

QSharedPointer<TextMessage> TxtMsgAssembler::assemble()
{
    TextMessage* ret = NULL;

    if(!m_type.isEmpty())
    {

        ret = makeMessage();
    }
    else
    {
        if(makeTypeAndLength())
        {
            ret = makeMessage();
        }
    }

    return QSharedPointer<TextMessage>(ret);
}

void TxtMsgAssembler::reset()
{
    m_type.clear();
    m_data.clear();
    m_length = 0;

}
