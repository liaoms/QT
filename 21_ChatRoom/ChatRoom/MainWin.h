#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include "QLoginDialog.h"
#include "TextMessage.h"
#include "TxtMsgAssembler.h"
#include "TxtMsgHandle.h"
#include "TCPClient.h"

class MainWin : public QWidget , public TxtMsgHandle
{
    Q_OBJECT
private:
    typedef void (MainWin::*MsgHandle)(QTcpSocket*, TextMessage&);

    QGroupBox m_OperatorGroup;
    QLineEdit m_lineEdit;
    QLabel m_lable;
    QPushButton m_LoginBtn;
    QPushButton m_cancelBtn;
    QPushButton m_sendBtn;

    QGroupBox m_MsgGroup;
    QPlainTextEdit m_plainTextEdit;

    TCPClient m_client;
    QLoginDialog m_login;

    QMap<QString, MsgHandle> m_mapHandle;

private:
    void initMember();
    bool InitMsgGrp();
    bool InitOpratorGrp();
    bool initUI();

    void connectSlots();
    void enableCtrl(bool enable);

    bool construct();

    void CONN_handle(QTcpSocket* socket, TextMessage& message);
    void DSCN_handle(QTcpSocket* socket, TextMessage& message);
    void LIER_handle(QTcpSocket* socket, TextMessage& message);
    void LIOK_handle(QTcpSocket* socket, TextMessage& message);
    void MSGA_handle(QTcpSocket* socket, TextMessage& message);

    MainWin(QWidget *parent = 0);
public:
    static MainWin* NewInstance();
    void handle(QTcpSocket* socket, TextMessage& message);
    ~MainWin();

protected slots:
    void onLoginBtnClicked();
    void onCancelBtnClicked();
    void onSendBtnClicked();
};

#endif // MAINWIN_H
