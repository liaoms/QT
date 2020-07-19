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

void TxtMsgAssembler::makeTypeAndLength()
{
    if(m_MsgQueue.length() > 8)
    {
        QString len = "";
        for(int i=0; i<4; i++)
        {
            m_type.append(m_MsgQueue.dequeue());
        }

        for(int i=0; i<4; i++)
        {
            len.append(m_MsgQueue.dequeue());
        }

        bool ret =true;
        m_length = len.toInt(&ret, 16);

        if(!ret)
        {
            reset();
        }
    }
}

TextMessage* TxtMsgAssembler::makeMessage()
{
    TextMessage* ret = NULL;
    int Len = (m_length - m_data.length()) < m_MsgQueue.length() ? m_length : m_MsgQueue.length();

    for(int i=0; i<Len; i++)
    {
        m_data.append(m_MsgQueue.dequeue());
    }

    if((m_data.length() == m_length) && (m_length > 0))
    {
        ret = new TextMessage(m_type, m_data);

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
        makeTypeAndLength();
        ret = makeMessage();
    }

    return QSharedPointer<TextMessage>(ret);
}

void TxtMsgAssembler::reset()
{
    m_type.clear();
    m_data.clear();
    m_length = 0;

}
