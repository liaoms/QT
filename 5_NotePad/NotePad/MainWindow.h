#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    MainWindow();
    MainWindow(const MainWindow& obj);
    MainWindow& operator = (const MainWindow& obj);

    bool construct();

    bool initMenuBar();
    bool initFileMenu(QMenuBar* mb);
    bool initEditMenu(QMenuBar* mb);
    bool initFormatMenu(QMenuBar* mb);
    bool initViewMenu(QMenuBar* mb);
    bool initHelpMenu(QMenuBar* mb);

    bool makeAction(QAction*& action, QString text, int key);
public:

    static MainWindow* NewInstance();

    ~MainWindow();
};

#endif // MAINWINDOW_H
