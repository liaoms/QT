#include "Widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>


Widget::Widget(QWidget *parent) : QWidget(parent),
    SimpleMsgBtn(this), CustomMsgBtn(this), OpenFileBtn(this), SaveFileBtn(this), ColorBtn(this)
{
    SimpleMsgBtn.setText("Simple Message Dialog");
    SimpleMsgBtn.move(20, 20);
    SimpleMsgBtn.resize(180, 30);

    CustomMsgBtn.setText("Custom Message Dialog");
    CustomMsgBtn.move(20, 70);
    CustomMsgBtn.resize(180, 30);

    OpenFileBtn.setText("Open File Dialog");
    OpenFileBtn.move(20, 120);
    OpenFileBtn.resize(180, 30);

    SaveFileBtn.setText("Save File Dialog");
    SaveFileBtn.move(20, 170);
    SaveFileBtn.resize(180, 30);

    ColorBtn.setText("Color Dialog");
    ColorBtn.move(20, 220);
    ColorBtn.resize(180, 30);

    setFixedSize(220, 270);

    connect(&SimpleMsgBtn, SIGNAL(clicked()), this, SLOT(SimpleMsgBtn_Clicked()));
    connect(&CustomMsgBtn, SIGNAL(clicked()), this, SLOT(CustomMsgBtn_Clicked()));
    connect(&OpenFileBtn, SIGNAL(clicked()), this, SLOT(OpenFileBtn_Clicked()));
    connect(&SaveFileBtn, SIGNAL(clicked()), this, SLOT(SaveFileBtn_Clicked()));
    connect(&ColorBtn, SIGNAL(clicked()), this, SLOT(ColorBtn_Clicked()));
}

void Widget::SimpleMsgBtn_Clicked()
{
    QMessageBox msg(this);

    msg.setText("This is a message dialog!");

    msg.exec();
}

void Widget::CustomMsgBtn_Clicked()
{
    QMessageBox msg(this);

    msg.setWindowTitle("Window Title");
    msg.setText("This is a detail message dialog!");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::YesToAll);

    if( msg.exec() == QMessageBox::Ok )
    {
        qDebug() << "Ok button is clicked!";
    }
}

void Widget::OpenFileBtn_Clicked()
{
    QFileDialog dlg(this);

    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setNameFilter("*.c *.cpp *.h");
    dlg.setFileMode(QFileDialog::ExistingFiles);

    if( dlg.exec() == QFileDialog::Accepted )
    {
        QStringList fs = dlg.selectedFiles();

        for(int i=0; i<fs.count(); i++)
        {
            qDebug() << fs[i];
        }
    }
}

void Widget::SaveFileBtn_Clicked()
{
    QFileDialog dlg(this);

    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setFilter(QDir::Readable | QDir::Writable);

    if( dlg.exec() == QFileDialog::Accepted )
    {
        QStringList fs = dlg.selectedFiles();

        for(int i=0; i<fs.count(); i++)
        {
            qDebug() << fs[i];
        }
    }
}

void Widget::ColorBtn_Clicked()
{
    QColorDialog dlg(this);

    dlg.setWindowTitle("Color");
    dlg.setCurrentColor(Qt::red);

    if(QColorDialog::Accepted == dlg.exec())
    {
        QColor color = dlg.selectedColor();

        qDebug() << color;
        qDebug() << color.red();
        qDebug() << color.green();
        qDebug() << color.blue();
    }

    /* 效果与通过exec()函数返回一样
    QColor color = dlg.selectedColor();

    qDebug() << color;
    qDebug() << color.red();
    qDebug() << color.green();
    qDebug() << color.blue();
    */
}

Widget::~Widget()
{
    
}
