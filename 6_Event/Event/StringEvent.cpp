#include "StringEvent.h"

StringEvent::StringEvent(QString data, Type type) : QEvent(type)
{
    m_data = data;
}

QString StringEvent::data()
{
    return m_data;
}
