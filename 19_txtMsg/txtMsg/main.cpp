#include <QCoreApplication>
#include <QDebug>
#include "TextMessage.h"
#include <TxtMsgAssembler.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TextMessage t("AAA", "123你好世界");

    QByteArray msg = t.serialize();

    qDebug() << "msg = " << msg;
    qDebug() << "type = " << t.type();
    qDebug() << "length = " << t.length();
    qDebug() << "data = " << t.data();

    TxtMsgAssembler ta;
    ta.prepare(msg.data(), msg.length());

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
