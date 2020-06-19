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
    bool initToolBar();

    bool initFileMenu(QMenuBar* mb);
    bool initEditMenu(QMenuBar* mb);
    bool initFormatMenu(QMenuBar* mb);
    bool initViewMenu(QMenuBar* mb);
    bool initHelpMenu(QMenuBar* mb);
    bool initFileToolItem(QToolBar* tb);
    bool initEditToolItem(QToolBar* tb);
    bool initFormatToolItem(QToolBar* tb);
    bool initViewToolItem(QToolBar* tb);

    bool makeAction(QAction*& action, QString text, int key);
    bool makeAction(QAction*& action, QString tip, QString icon);
public:

    static MainWindow* NewInstance();

    ~MainWindow();
};

#endif // MAINWINDOW_H
