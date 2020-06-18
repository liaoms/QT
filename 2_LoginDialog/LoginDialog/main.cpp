#include "Widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ret = -1;
    Widget* w = Widget::NewInstance();


    if(NULL != w)
    {
        w->setWindowTitle("Welcome");
        w->show();

        ret = a.exec();

        delete w;
        w = NULL;
    }

    return ret;
}
