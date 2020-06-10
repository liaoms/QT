#include "CalculatorUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorUI* w = CalculatorUI::NewInstance();

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
