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
    }
    return ret;
}

bool MainWin::InitMsgGrp()
{
    bool ret = true;
    QPlainTextEdit* plainTextEdit = new QPlainTextEdit(this);
    QVBoxLayout* vLayOut = new QVBoxLayout();

    ret = (plainTextEdit && vLayOut);

    if(ret)
    {
        vLayOut->addWidget(plainTextEdit);
        m_MsgGroup.setLayout(vLayOut);
    }

    return ret;
}
bool MainWin::InitOpratorGrp()
{
    bool ret = true;
    QLineEdit* lineEdit = new QLineEdit(this);
    QLabel* lable = new QLabel(this);
    QPushButton* cancelBtn = new QPushButton(this);
    QPushButton* sendBtn = new QPushButton(this);

    QGridLayout* gLayout = new QGridLayout();

    ret = (lineEdit && lable && cancelBtn && sendBtn && gLayout);

    if(ret)
    {
        lineEdit->setFixedHeight(30);
        lable->setText("聊天软件");
        cancelBtn->setText("取消");
        sendBtn->setText("发送");

        gLayout->addWidget(lineEdit, 0, 0, 1, 5);
        gLayout->addWidget(lable, 1, 0, 1, 1);
        gLayout->addWidget(sendBtn, 1, 3, 1, 1);
        gLayout->addWidget(cancelBtn, 1, 4, 1, 1);

        m_OperatorGroup.setLayout(gLayout);
    }

    return ret;

}

MainWin::~MainWin()
{

}
