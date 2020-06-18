#include "CalculatorUI.h"
#include <QDebug>
#include <QString>

CalculatorUI::CalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{

}

bool CalculatorUI::construct()
{
    bool ret = true;

    const char* btnText[20] =
        {
            "7", "8", "9", "+", "(",
            "4", "5", "6", "-", ")",
            "1", "2", "3", "*", "<-",
            "0", ".", "=", "/", "C",
        };

    m_pLineEdit = new QLineEdit(this);
    if(NULL != m_pLineEdit)
    {
        m_pLineEdit->setReadOnly(true);
        m_pLineEdit->resize(240, 30);
        m_pLineEdit->move(10, 10);
        m_pLineEdit->setAlignment(Qt::AlignRight);
    }
    else
    {
        ret = false;
    }

     for(int i=0; (i<4) && ret; i++)
     {
        for(int j=0; (j<5) && ret; j++)
        {
            m_pButton[i*5 + j] = new QPushButton(this);

            if(NULL != m_pButton[i*5 + j])
            {
                m_pButton[i*5 + j]->resize(40, 40);
                m_pButton[i*5 + j]->move(10 + (10 + 40)*j, 50 + (10 + 40)*i);
                m_pButton[i*5 + j]->setText(btnText[i*5 + j]);
                connect( m_pButton[i*5 + j], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
            }
            else
            {
                ret = false;
                break;
            }
        }
     }
     return ret;
}

CalculatorUI* CalculatorUI::NewInstance()
{
    CalculatorUI* ret = new CalculatorUI();

    if( (NULL == ret) || (!ret->construct()) )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

//设置接口
void CalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}

//返回使用的接口
ICalculator* CalculatorUI::getCalculator()
{
    return m_cal;
}

void CalculatorUI::show()
{
    QWidget::show();
}

void CalculatorUI::onButtonClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());

    if(NULL != btn)
    {
        QString str = btn->text();
        if("<-" == str)
        {
            QString lineText = m_pLineEdit->text();

            lineText.remove(lineText.length() - 1, 1);
            m_pLineEdit->setText(lineText);
        }
        else if("C" == str)
        {
            m_pLineEdit->clear();
        }
        else if("=" == str)
        {
            m_cal->expression(m_pLineEdit->text());  //使用计算接口
            m_pLineEdit->setText(m_cal->result());      //使用获取结果接口
        }
        else
        {
            QString lineText = m_pLineEdit->text() + str;
            m_pLineEdit->setText(lineText);
        }
    }

}

CalculatorUI::~CalculatorUI()
{
    if(m_pLineEdit)
    {
        delete m_pLineEdit;
        m_pLineEdit = NULL;
    }

    for(int i=0; i<20; i++)
    {
        delete m_pButton[i];
        m_pButton[i] = NULL;
    }
}
