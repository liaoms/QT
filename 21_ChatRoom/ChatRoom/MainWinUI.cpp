#include "MainWin.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QThread>

MainWin::MainWin(QWidget *parent)
    : QWidget(parent)
{
    m_mapHandle.insert("CONN", CONN_handle);
    m_mapHandle.insert("DSCN", DSCN_handle);
    m_mapHandle.insert("LIOK", LIOK_handle);
    m_mapHandle.insert("LIER", LIER_handle);
    m_mapHandle.insert("MSGA", MSGA_handle);
}

bool MainWin::construct()
{
    initMember();
    bool ret = initUI();
    return ret;
}


MainWin* MainWin::NewInstance()
{
    MainWin* ret = new MainWin();

    if( !(ret && ret->construct()))
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void MainWin::connectSlots()
{
    connect(&m_LoginBtn,SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
    connect(&m_cancelBtn,SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
    connect(&m_sendBtn, SIGNAL(clicked()), this, SLOT(onSendBtnClicked()));
}

void MainWin::enableCtrl(bool enable)
{
    m_lineEdit.setEnabled(enable);
    m_sendBtn.setEnabled(enable);
    m_cancelBtn.setEnabled(enable);

    if(enable)
    {
        m_LoginBtn.setText("断开登陆");
        m_lable.setText("已连接");
    }
    else
    {
        m_LoginBtn.setText("登陆");
        m_lable.setText("未连接");
        m_lineEdit.clear();
        m_plainTextEdit.clear();
    }
}

bool MainWin::initUI()
{
    bool ret =true;
    ret = InitMsgGrp();
    ret = ret && InitOpratorGrp();

    if(ret)
    {
        QVBoxLayout* MainLayout = new QVBoxLayout();

        m_MsgGroup.setParent(this);
        m_MsgGroup.setTitle("消息框");

        m_OperatorGroup.setParent(this);
        m_OperatorGroup.setTitle("用户名");
        m_OperatorGroup.setFixedHeight(150);

        MainLayout->addWidget(&m_MsgGroup);
        MainLayout->addWidget(&m_OperatorGroup);


        setLayout(MainLayout);

        setFixedSize(600, 450);

        connectSlots();
        enableCtrl(false);
    }
    return ret;
}

bool MainWin::InitMsgGrp()
{
    bool ret = true;
    m_plainTextEdit.setParent(this);
    QVBoxLayout* vLayOut = new QVBoxLayout();

    if(vLayOut)
    {
        vLayOut->addWidget(&m_plainTextEdit);
        m_MsgGroup.setLayout(vLayOut);
    }

    return ret;
}
bool MainWin::InitOpratorGrp()
{
    bool ret = true;
    m_lineEdit.setParent(this);
    m_lineEdit.setFixedHeight(30);
    m_lineEdit.setFixedHeight(30);

    m_lable.setParent(this);
    m_lable.setText("未连接");

    m_LoginBtn.setParent(this);
    m_LoginBtn.setText("登陆");

    m_cancelBtn.setParent(this);
    m_cancelBtn.setText("取消");

    m_sendBtn.setParent(this);
    m_sendBtn.setText("发送");

    QGridLayout* gLayout = new QGridLayout();

    if(gLayout)
    {
        gLayout->addWidget(&m_lineEdit, 0, 0, 1, 5);
        gLayout->addWidget(&m_lable, 1, 0, 1, 1);
        gLayout->addWidget(&m_LoginBtn, 1, 2, 1, 1);
        gLayout->addWidget(&m_sendBtn, 1, 3, 1, 1);
        gLayout->addWidget(&m_cancelBtn, 1, 4, 1, 1);

        m_OperatorGroup.setLayout(gLayout);
    }

    return ret;

}

MainWin::~MainWin()
{
    m_client.close();
}
