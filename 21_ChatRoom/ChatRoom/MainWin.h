#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include "QLoginDialog.h"

class MainWin : public QWidget
{
    Q_OBJECT
private:
    QGroupBox m_OperatorGroup;
    QGroupBox m_MsgGroup;

private:
    bool InitMsgGrp();
    bool InitOpratorGrp();
    bool initUI();

    bool construct();

    MainWin(QWidget *parent = 0);
public:
    static MainWin* NewInstance();
    ~MainWin();
};

#endif // MAINWIN_H
