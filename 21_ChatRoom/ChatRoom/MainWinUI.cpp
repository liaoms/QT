#include "MainWin.h"
#include <QVBoxLayout>
#include <QGridLayout>

MainWin::MainWin(QWidget *parent)
    : QWidget(parent)
{

}

bool MainWin::construct()
{
    QLoginDialog login(this);

    bool ret = true;

    if(login.exec() == QDialog::Accepted)
    {

        ret = (login.getUser().trimmed() == "lms") && ("111111" == login.getPwd());
        if( ret )
        {
            ret = initUI();
        }
    }
    else
    {
        ret = false;
    }

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
    connect(&m_cancelBtn,SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
    connect(&m_sendBtn, SIGNAL(clicked()), this, SLOT(onSendBtnClicked()));
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
        m_OperatorGroup.setTitle("操作框");
        m_OperatorGroup.setFixedHeight(150);

        MainLayout->addWidget(&m_MsgGroup);
        MainLayout->addWidget(&m_OperatorGroup);


        setLayout(MainLayout);

        setFixedSize(800, 600);

        connectSlots();
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
    m_lable.setText("聊天软件");

    m_cancelBtn.setParent(this);
    m_cancelBtn.setText("取消");

    m_sendBtn.setParent(this);
    m_sendBtn.setText("发送");

    QGridLayout* gLayout = new QGridLayout();

    if(gLayout)
    {
        gLayout->addWidget(&m_lineEdit, 0, 0, 1, 5);
        gLayout->addWidget(&m_lable, 1, 0, 1, 1);
        gLayout->addWidget(&m_sendBtn, 1, 3, 1, 1);
        gLayout->addWidget(&m_cancelBtn, 1, 4, 1, 1);

        m_OperatorGroup.setLayout(gLayout);
    }

    return ret;

}

MainWin::~MainWin()
{

}
