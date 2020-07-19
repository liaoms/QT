#include <QCoreApplication>
#include <QDebug>
#include "TextMessage.h"
#include <TxtMsgAssembler.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TextMessage t("AAA", "1234567890abcdefg");

    QString msg = t.serialize();

    TxtMsgAssembler ta;
    ta.prepare(msg.toStdString().c_str(), msg.length());

    QSharedPointer<TextMessage> p = ta.assemble();

    if(!p.isNull())
    {
        qDebug() << "action1 begin";
        qDebug() << "msg = " << p->serialize();
        qDebug() << "type = " << p->type();
        qDebug() << "length = " << p->length();
        qDebug() << "data = " << p->data();
        qDebug() << "action1 end\n";
    }

    char str1[] = "AAA 4   ";
    ta.prepare(str1, strlen(str1));
     p = ta.assemble();

    if(p)
    {
        qDebug() << "action2 begin";
        qDebug() << "msg = " << p->serialize();
        qDebug() << "type = " << p->type();
        qDebug() << "length = " << p->length();
        qDebug() << "data = " << p->data();
        qDebug() << "action2 end\n";
    }

    char str2[] = "abc";
    ta.prepare(str2, strlen(str2));
     p = ta.assemble();

    if(p)
    {
        qDebug() << "action3 begin";
        qDebug() << "msg = " << p->serialize();
        qDebug() << "type = " << p->type();
        qDebug() << "length = " << p->length();
        qDebug() << "data = " << p->data();
        qDebug() << "action3 end\n";
    }

    char str3[] = "a";
    ta.prepare(str3, strlen(str3));
     p = ta.assemble();

    if(p)
    {
        qDebug() << "action4 begin";
        qDebug() << "msg = " << p->serialize();
        qDebug() << "type = " << p->type();
        qDebug() << "length = " << p->length();
        qDebug() << "data = " << p->data();
        qDebug() << "action4 end\n";
    }

    return a.exec();
}
