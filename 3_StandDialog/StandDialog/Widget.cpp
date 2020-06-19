#include "Widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QFontDialog>
#include <QProgressDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QPrinter>

Widget::Widget(QWidget *parent) : QWidget(parent),
    SimpleMsgBtn(this), CustomMsgBtn(this), OpenFileBtn(this), SaveFileBtn(this), ColorBtn(this),
    InputBtn(this), FontBtn(this), ProgressBtn(this), PrintBtn(this)
{
    SimpleMsgBtn.setText("Simple Message Dialog");
    SimpleMsgBtn.move(20, 20);
    SimpleMsgBtn.resize(220, 30);

    CustomMsgBtn.setText("Custom Message Dialog");
    CustomMsgBtn.move(20, 70);
    CustomMsgBtn.resize(220, 30);

    OpenFileBtn.setText("Open File Dialog");
    OpenFileBtn.move(20, 120);
    OpenFileBtn.resize(220, 30);

    SaveFileBtn.setText("Save File Dialog");
    SaveFileBtn.move(20, 170);
    SaveFileBtn.resize(220, 30);

    ColorBtn.setText("Color Dialog");
    ColorBtn.move(20, 220);
    ColorBtn.resize(220, 30);

    InputBtn.setText("Input Dialog");
    InputBtn.move(20, 270);
    InputBtn.resize(220, 30);

    FontBtn.setText("Font Dialog");
    FontBtn.move(20, 320);
    FontBtn.resize(220, 30);

    ProgressBtn.setText("Progress Dialog");
    ProgressBtn.move(20, 370);
    ProgressBtn.resize(220, 30);

    PrintBtn.setText("Printer Dialog");
    PrintBtn.move(20, 420);
    PrintBtn.resize(220, 30);

    setFixedSize(260, 470);

    connect(&SimpleMsgBtn,  SIGNAL(clicked()), this, SLOT(SimpleMsgBtn_Clicked()));
    connect(&CustomMsgBtn,  SIGNAL(clicked()), this, SLOT(CustomMsgBtn_Clicked()));
    connect(&OpenFileBtn,   SIGNAL(clicked()), this, SLOT(OpenFileBtn_Clicked()));
    connect(&SaveFileBtn,   SIGNAL(clicked()), this, SLOT(SaveFileBtn_Clicked()));
    connect(&ColorBtn,      SIGNAL(clicked()), this, SLOT(ColorBtn_Clicked()));
    connect(&InputBtn,      SIGNAL(clicked()), this, SLOT(InputBtn_Clicked()));
    connect(&FontBtn,       SIGNAL(clicked()), this, SLOT(FontBtn_Clicked()));
    connect(&ProgressBtn,   SIGNAL(clicked()), this, SLOT(ProgressBtn_Clicked()));
    connect(&PrintBtn,      SIGNAL(clicked()), this, SLOT(PrintBtn_Clicked()));
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

void Widget::InputBtn_Clicked()
{
    QInputDialog dlg(this);

    dlg.setWindowTitle("Input");
    dlg.setInputMode(QInputDialog::IntInput);
    dlg.setIntMinimum(0);
    dlg.setIntMaximum(255);

    if(QInputDialog::Accepted == dlg.exec())
    {
        qDebug() << dlg.intValue();
    }

    /*   //此效果与上述代码一致
    int ret = QInputDialog::getInt(this, "Input", "please Input a value", 0, 0 , 255);
    qDebug() << ret;
    */
}

void Widget::FontBtn_Clicked()
{
    QFontDialog dlg(this);
    dlg.setWindowTitle("Font");

    if(QFontDialog::Accepted == dlg.exec())
    {
        qDebug() << dlg.selectedFont();

        FontBtn.setFont(dlg.selectedFont());
    }

    //此句跟上述代码效果一致
    //FontBtn.setFont(QFontDialog::getFont(NULL));
}

void Widget::ProgressBtn_Clicked()
{
    QProgressDialog dlg(this);

    dlg.setWindowTitle("Progress");
    dlg.setLabelText("Download ...");
    dlg.setMinimum(0);
    dlg.setMaximum(100);

    dlg.setValue(0);

    //创建一个线程，转用于更新进度条

    dlg.exec();

}

void Widget::PrintBtn_Clicked()
{
    QPrintDialog dlg(this);
    dlg.setWindowTitle("Printer");

    if(QPrintDialog::Accepted == dlg.exec())
    {
        QPrinter *p = dlg.printer();
        p->setOutputFileName("E:\\DTSoftWare\\Qt\\test.xps");

        QTextDocument td;
        //td.setPlainText("Hello World");
        td.setHtml("<h1>Print html object test</hl>");

        td.print(p);
    }
}

Widget::~Widget()
{
    
}
