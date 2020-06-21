#include "Widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_lineEdit(this), m_lineEdit1(this)
{
    resize(400, 300);
    m_lineEdit.move(10, 10);
    m_lineEdit1.move(10, 40);

    m_lineEdit.installEventFilter(this);    //组件m_lineEdit注册事件过滤器
    m_lineEdit1.installEventFilter(this);   //组件m_lineEdit1注册事件过滤器
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
                ret = false;
                    break;

                default:
                    break;
            }
        }
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
