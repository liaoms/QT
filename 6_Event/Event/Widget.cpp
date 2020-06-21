#include "Widget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_lineEdit(this), m_lineEdit1(this), m_delBtn(this), m_delBtn1(this)
{
    resize(400, 300);
    initUI();

    connect(&m_delBtn, SIGNAL(clicked()), this, SLOT(ondelBtnClicked()));
    connect(&m_delBtn1, SIGNAL(clicked()), this, SLOT(ondelBtn1Clicked()));
    connect(&m_delBtn2, SIGNAL(clicked()), this, SLOT(ondelBtn2Clicked()));

    m_lineEdit.installEventFilter(this);    //组件m_lineEdit注册事件过滤器
    m_lineEdit1.installEventFilter(this);   //组件m_lineEdit1注册事件过滤器
    m_lineEdit2.installEventFilter(this);
}

void Widget::initUI()
{
    m_delBtn.setText("delBtn");
    m_delBtn1.setText("delBtn1");
    m_delBtn2.setText("delBtn2");

    QVBoxLayout* pVBlayoutAll = new QVBoxLayout();
    QVBoxLayout* pVBLayout = new QVBoxLayout();
    QHBoxLayout* pHBLayout = new QHBoxLayout();


    pVBLayout->addWidget(&m_lineEdit);
    pVBLayout->addWidget(&m_lineEdit1);
    pVBLayout->addWidget(&m_lineEdit2);

    pHBLayout->addWidget(&m_delBtn);
    pHBLayout->addWidget(&m_delBtn1);
    pHBLayout->addWidget(&m_delBtn2);

    pVBlayoutAll->addLayout(pVBLayout, 4);
    pVBlayoutAll->addLayout(pHBLayout, 4);

    setLayout(pVBlayoutAll);

}

//点击按键，等同于聚焦到m_lineEdit中，退格删除一个字符
void Widget::ondelBtnClicked()
{
    //自定义退格键的按下和松开事件
    QKeyEvent keyPress(QKeyEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    QKeyEvent keyRelease(QKeyEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier);

    //发送自定义事件到m_lineEdit (效果等同于直接按退格键删除m_lineEdit中的一个字符)
    QApplication::sendEvent(&m_lineEdit, &keyPress);
    QApplication::sendEvent(&m_lineEdit, &keyRelease);

    //sendEvent方式发送的事件为阻塞时间，等事件处理函数处理完后，才往下执行，可发送栈上和堆上申请的事件
}

//点击按键，等同于聚焦到m_lineEdit1中，退格删除一个字符
void Widget::ondelBtn1Clicked()
{
    //自定义退格键的按下和松开事件
    QKeyEvent* pKeyPress = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    QKeyEvent* pKeyRelease = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier);

    //发送自定义事件到m_lineEdit (效果等同于直接按退格键删除m_lineEdit1中的一个字符)
    QApplication::postEvent(&m_lineEdit1, pKeyPress);
    QApplication::postEvent(&m_lineEdit1, pKeyRelease);

    //postEvent方式发送的事件为非阻塞时间，发送完后直接往下执行，事件会进入事件队列等待处理，所以只能发送堆上申请的事件
}

void Widget::ondelBtn2Clicked()
{
    StringEvent sEvent("LMS");

    //发送自定义事件到m_lineEdit2组件对象
    QApplication::sendEvent( &m_lineEdit2, &sEvent);
}

//按键按下事件先经过总事件处理函数，再经过按键按下事件处理函数
bool Widget::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        qDebug() << "Widget::event";
    }

    return QWidget::event(event);   //直接调用父类默认事件处理函数
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Widget::keyPressEvent";

    QWidget::keyPressEvent(event);  //直接调用父类默认事件处理函数
}

//重写事件过滤器
// return true - 已经正常处理，不需要传递到watched对象
// false - 正常传递到watched对象
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    bool ret = true;
    //删选指定对象的指定事件
    if( QEvent::KeyPress == event->type() )
    {
        QKeyEvent* e = dynamic_cast<QKeyEvent*>(event);

        if(&m_lineEdit == watched)
        {
            switch (e->key())   //m_lineEdit 只接受0-9数字输入
            {
                case Qt::Key_0:
                case Qt::Key_1:
                case Qt::Key_2:
                case Qt::Key_3:
                case Qt::Key_4:
                case Qt::Key_5:
                case Qt::Key_6:
                case Qt::Key_7:
                case Qt::Key_8:
                case Qt::Key_9:
                case Qt::Key_Backspace:   //补充接收退格键
                ret = false;
                    break;

                default:
                    break;
            }
        }
        else if(&m_lineEdit1 == watched)
        {
            switch (e->key())  //m_lineEdit1 只接受A-H字母输入
            {
                case Qt::Key_A:
                case Qt::Key_B:
                case Qt::Key_C:
                case Qt::Key_D:
                case Qt::Key_E:
                case Qt::Key_F:
                case Qt::Key_G:
                case Qt::Key_H:
                case Qt::Key_Backspace:
                ret = false;
                    break;

                default:
                    break;
            }
        }
    }
    else if(StringEvent::strTYPE == event->type())  //事件过滤器中设置对自定义事件的监控
    {
        StringEvent* e = dynamic_cast<StringEvent*>(event);

        if(&m_lineEdit2 == watched)
        {
            m_lineEdit2.insert(e->data());
        }
        ret = false;
    }
    else
    {
        ret = QWidget::eventFilter(watched, event);
    }
    return ret;
}

Widget::~Widget()
{

}
