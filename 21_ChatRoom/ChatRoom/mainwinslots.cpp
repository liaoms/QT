#include "MainWin.h"
#include <QDebug>
#include <QMessageBox>

void MainWin::initMember()
{
    m_client.setHandle(this);
}

void MainWin::onLoginBtnClicked()
{
    if(!m_client.isValid())
    {
        if(m_login.exec() == QDialog::Accepted)
        {
            QString user = m_login.getUser().trimmed();
            QString pwd = m_login.getPwd();

            if(m_client.connectTo("127.0.0.1", 8080))
            {
                TextMessage msg("LGIN", user + "\r" + pwd);
                m_client.write(msg);
            }
            else
            {
                QMessageBox::critical(this, "错误", "无法连接远程服务器");
            }
        }
    }
    else
    {
        m_client.close();
        enableCtrl(false);
        m_OperatorGroup.setTitle("用户名");
    }

}

void MainWin::onCancelBtnClicked()
{

}
void MainWin::onSendBtnClicked()
{
    QString data = m_OperatorGroup.title() + ":\n" + "    " + m_lineEdit.text() + "\n";

    TextMessage msg("MSGA", data);
    m_client.write(msg);
    m_lineEdit.clear();
}

void MainWin::handle(QTcpSocket* socket, TextMessage& message)
{
    if(m_mapHandle.contains(message.type()))
    {
        MsgHandle handle = m_mapHandle.value(message.type());

        (this->*handle)(socket, message);
    }
}

void MainWin::CONN_handle(QTcpSocket* socket, TextMessage& message)
{

}
void MainWin::DSCN_handle(QTcpSocket* socket, TextMessage& message)
{

}

void MainWin::LIER_handle(QTcpSocket* socket, TextMessage& message)
{
    QMessageBox::critical(this, "错误", "用户名或密码错误,无法登陆服务器");
    enableCtrl(false);
    m_client.close();
}
void MainWin::LIOK_handle(QTcpSocket* socket, TextMessage& message)
{
    QString usr = message.data().mid(0, message.data().indexOf('\r'));
    m_OperatorGroup.setTitle(usr);
    enableCtrl(true);
}

void MainWin::MSGA_handle(QTcpSocket* socket, TextMessage& message)
{
    m_plainTextEdit.appendPlainText(message.data());
}
