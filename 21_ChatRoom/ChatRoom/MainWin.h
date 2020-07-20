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
    QLineEdit m_lineEdit;
    QLabel m_lable;
    QPushButton m_cancelBtn;
    QPushButton m_sendBtn;

    QGroupBox m_MsgGroup;
    QPlainTextEdit m_plainTextEdit;

private:
    bool InitMsgGrp();
    bool InitOpratorGrp();
    bool initUI();

    void connectSlots();

    bool construct();

    MainWin(QWidget *parent = 0);
public:
    static MainWin* NewInstance();
    ~MainWin();

protected slots:
    void onCancelBtnClicked();
    void onSendBtnClicked();
};

#endif // MAINWIN_H
