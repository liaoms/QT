#ifndef __QLOGINDIALOG_H__
#define __QLOGINDIALOG_H__

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class QLoginDialog : public QDialog
{
    Q_OBJECT
private:
    QLabel UserLabel;
    QLabel PwdLabel;
    QLineEdit UserEdit;
    QLineEdit PwdEdit;
    QPushButton LoginBtn;
    QPushButton CancelBtn;
    QString m_user;
    QString m_pwd;
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
