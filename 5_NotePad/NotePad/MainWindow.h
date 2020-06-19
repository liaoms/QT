#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit mainEditor;
    QLabel statusLbl;
    QString m_filePath;
    bool m_isTextChanged;

    MainWindow();
    MainWindow(const MainWindow& obj);
    MainWindow& operator = (const MainWindow& obj);

    bool construct();

    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();
    bool initMainEditor();

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

    QString showFileDialog(QFileDialog::AcceptMode mode, QString title);
    int showQueryMessage(QString message);
    void showErrorMessage(QString message);
    QString saveCurrentData(QString path = "");
    void preEditorChange();

private slots:
        void onFileNew();
        void onFileOpen();
        void onFileSave();
        void onFileSaveAs();
        void onTextChanged();

protected:
    void closeEvent(QCloseEvent* event);

public:

    static MainWindow* NewInstance();   //重写关闭事件

    ~MainWindow();
};

#endif // MAINWINDOW_H
