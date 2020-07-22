#include "MainWin.h"
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

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

//发送消息
void MainWin::onSendBtnClicked()
{
    QString usr = getCheckedUser();

    if(usr.isEmpty())
    {
        QString data = m_OperatorGroup.title() + ":\n" + "    " + m_lineEdit.text() + "\n";
        TextMessage msg("MSGA", data);
        m_client.write(msg);
    }
    else
    {
        usr.append('\r');
        usr.append(m_OperatorGroup.title());
        usr.append('\r');

        QString data = usr + m_OperatorGroup.title() + ":\n" + "    " + m_lineEdit.text() + "\n";

        TextMessage msg("MSGP", data);
        m_client.write(msg);
    }

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

//登录失败
void MainWin::LIER_handle(QTcpSocket* socket, TextMessage& message)
{
    QMessageBox::critical(this, "错误", "用户名或密码错误,无法登陆服务器");
    enableCtrl(false);
    m_client.close();
}

//登录成功
void MainWin::LIOK_handle(QTcpSocket* socket, TextMessage& message)
{
    QString usr = message.data().mid(0, message.data().indexOf('\r'));
    m_OperatorGroup.setTitle(usr);
    this->setWindowTitle(usr);
    enableCtrl(true);
}

//接收公有消息
void MainWin::MSGA_handle(QTcpSocket* socket, TextMessage& message)
{
    m_plainTextEdit.appendPlainText(message.data());
}

//接收私有消息
void MainWin::MSGP_handle(QTcpSocket* socket, TextMessage& message)
{
    m_plainTextEdit.appendPlainText(message.data());
}

//更新在线用户列表
void MainWin::USER_handle(QTcpSocket* socket, TextMessage& message)
{
    QStringList userList = message.data().split('\r');
    int childItems = m_listWidget.count();

    bool isExist = false;

    for(int i=0; i<userList.size(); i++)
    {
        isExist = false;
        for(int j=0; j<childItems; j++)
        {
            QListWidgetItem* item = m_listWidget.item(j);

            if(item->text() == userList[i])
            {
                isExist = true;
                break;
            }
        }

        if(!isExist)
        {
            QListWidgetItem* newItem = new QListWidgetItem(&m_listWidget);
            newItem->setText(userList[i]);
            if(userList[i] != m_OperatorGroup.title())
            {
                newItem->setCheckState(Qt::Unchecked);
            }
            m_listWidget.addItem(newItem);
        }
    }

    QList<QListWidgetItem*> removList;
    for(int i=0; i<childItems; i++)
    {
        isExist = false;
        QListWidgetItem* item = m_listWidget.item(i);
        for(int j=0; j<userList.size(); j++)
        {
            if(item->text() == userList[j])
            {
                isExist = true;
                break;
            }
        }

        if(!isExist)
        {
            removList.append(item);
        }
    }

    for(int i=0; i<removList.size(); i++)
    {
        int index = m_listWidget.row(removList[i]);

        delete m_listWidget.takeItem(index);
    }
}
