#include "MainWin.h"
#include <QDebug>

void MainWin::initMember()
{
    m_client.setHandle(this);
}

void MainWin::onCancelBtnClicked()
{
    qDebug() << "onCancelBtnClicked";
}
void MainWin::onSendBtnClicked()
{
    qDebug() << "onSendBtnClicked";
}

void MainWin::handle(QTcpSocket* socket, TextMessage& message)
{
    qDebug() << socket;
    qDebug() << message.type();
    qDebug() << message.data();
}
