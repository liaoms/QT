#ifndef __QLOGINDIALOG_H__
#define __QLOGINDIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

class QLoginDialog : public QDialog
{
    Q_OBJECT
private:
    QGroupBox m_groupBox;

    QLabel m_UserNameLabel;
    QLabel m_PassWordLabel;
    QLineEdit m_UserNameEdit;
    QLineEdit m_PassWordEdit;

    QPushButton m_LoginButton;
    QPushButton m_ExitButton;

    QString m_UserName;
    QString m_PassWord;

private:
    void UiInit(); //登录对话框UI布局初始化
private slots:
    void LoginBtn_Clicked();
    void CancelBtn_Clicked();
public:
    QLoginDialog(QWidget *parent = 0);
    QString getUser();
    QString getPwd();
    ~QLoginDialog();
};


#endif
