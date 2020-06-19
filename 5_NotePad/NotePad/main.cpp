#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ret = 0;

    MainWindow *w = MainWindow::NewInstance();
    if(w)
    {
       w->showMaximized();
       //w->show();

       ret = a.exec();

       delete w;
        w = NULL;
    }
    return ret;
}
