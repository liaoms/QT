#include <QApplication>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculator* w = Calculator::NewInstance();

    int ret = -1;

    if(NULL != w)
    {
        w->show();

        ret = a.exec();

        delete w;
        w = NULL;
    }

    return ret;

}
