#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include "QLoginDialog.h"
#include "TextMessage.h"
#include "TxtMsgAssembler.h"
#include "TxtMsgHandle.h"
#include "TCPClient.h"

class MainWin : public QWidget , public TxtMsgHandle
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

    TCPClient m_client;

private:
    void initMember();
    bool InitMsgGrp();
    bool InitOpratorGrp();
    bool initUI();

    void connectSlots();

    bool construct();

    MainWin(QWidget *parent = 0);
public:
    static MainWin* NewInstance();
    void handle(QTcpSocket* socket, TextMessage& message);
    ~MainWin();

protected slots:
    void onCancelBtnClicked();
    void onSendBtnClicked();
};

#endif // MAINWIN_H
