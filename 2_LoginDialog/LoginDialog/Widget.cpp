#include "Widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget()
{
}

bool Widget::construct()
{
    QLoginDialog login(this);

    bool ret = true;

    if(login.exec() == QDialog::Accepted)
    {
        qDebug() << login.getUser().trimmed();
        qDebug() << login.getPwd();
    }
    else
    {
        ret = false;
    }

    return ret;
}

Widget* Widget::NewInstance()
{
    Widget* ret = new Widget();

    if((NULL == ret) || (!ret->construct()))
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

Widget::~Widget()
{

}
