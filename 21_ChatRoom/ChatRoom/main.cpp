#include "MainWin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWin* w = MainWin::NewInstance();

    if(w)
    {
        w->show();
    }


    return a.exec();
}
