#include "QLoginDialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

QLoginDialog::QLoginDialog(QWidget* parent) : QDialog(parent, Qt::WindowCloseButtonHint),
    m_UserNameLabel(this), m_PassWordLabel(this), m_UserNameEdit(this), m_PassWordEdit(this), m_LoginButton(this), m_ExitButton(this)
{
    UiInit();

    connect(&m_LoginButton, SIGNAL(clicked()), this, SLOT(LoginBtn_Clicked()));
    connect(&m_ExitButton, SIGNAL(clicked()), this, SLOT(CancelBtn_Clicked()));
}

void QLoginDialog::UiInit() //登录对话框UI布局初始化
{
    m_groupBox.setParent(this);
    m_groupBox.move(20, 20);
    m_groupBox.resize(260, 160);
    m_groupBox.setTitle("登录信息");

    m_UserNameLabel.setParent(&m_groupBox);
    m_UserNameLabel.setText("用户名");
    m_UserNameLabel.setFixedHeight(25);

    m_PassWordLabel.setParent(&m_groupBox);
    m_PassWordLabel.setText("密  码");
    m_PassWordLabel.setFixedHeight(25);

    m_UserNameEdit.setParent(&m_groupBox);
    m_PassWordEdit.setParent(&m_groupBox);
    m_UserNameEdit.setFixedHeight(25);
    m_PassWordEdit.setFixedHeight(25);
    m_PassWordEdit.setEchoMode(QLineEdit::Password); //密码格式输入

    m_LoginButton.setParent(this);
    m_LoginButton.setText("登录");
    m_LoginButton.setFixedHeight(25);

    m_ExitButton.setParent(this);
    m_ExitButton.setText("退出");
    m_ExitButton.setFixedHeight(25);

    QFormLayout *formLayout = new QFormLayout(&m_groupBox);
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    formLayout->addRow(&m_UserNameLabel, &m_UserNameEdit);
    formLayout->addRow(&m_PassWordLabel, &m_PassWordEdit);
    formLayout->setFormAlignment(Qt::AlignCenter);
    formLayout->setMargin(30);

    hBoxLayout->addWidget(&m_LoginButton);
    hBoxLayout->addWidget(&m_ExitButton);
    hBoxLayout->setSpacing(20);

    vBoxLayout->addWidget(&m_groupBox);
    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->setSpacing(10);

    setLayout(vBoxLayout);
}

void QLoginDialog::LoginBtn_Clicked()
{
    m_UserName = m_UserNameEdit.text().trimmed();
    m_PassWord = m_PassWordEdit.text();

    if(m_UserName.trimmed().isEmpty() || m_PassWord.isEmpty())
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "用户名或密码不能为空", QMessageBox::Ok, this);
        msgBox.exec();
    }
    else
    {
        done(Accepted);
    }
}

void QLoginDialog::CancelBtn_Clicked()
{
    done(Rejected);
}

QString QLoginDialog::getUser()
{
    return m_UserName.trimmed();
}

QString QLoginDialog::getPwd()
{
    return m_PassWord;
}

QLoginDialog::~QLoginDialog()
{

}

