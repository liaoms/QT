#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QProgressBar>
#include "AnotherThread.h"

class Widget : public QWidget
{
    Q_OBJECT
private:
    AnotherThread m_thread;
    QPlainTextEdit m_textEdit;
    QProgressBar m_progressBar;

private:
    void initUI();
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onUpdateUI(QString str);
};

#endif // WIDGET_H
