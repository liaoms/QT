#include <QCoreApplication>
#include <QDebug>
#include "TextMessage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TextMessage t("AAA", "1234567890abcdefg");

    QString msg = t.serialize();

    TextMessage t1;
    t1.unserialize(msg);

    qDebug() << msg;

    qDebug() << "t.type = " << t.type();
    qDebug() << "t.length = " << t.length();
    qDebug() << "t.data = " << t.data();

    qDebug() << "t1.type = " << t1.type();
    qDebug() << "t1.length = " << t1.length();
    qDebug() << "t1.data = " << t1.data();

    return a.exec();
}
