#include "CalculatorUI.h"
#include <QDebug>

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

void CalculatorUI::show()
{
    QWidget::show();
}

void CalculatorUI::onButtonClicked()
{
    QPushButton* btn = static_cast<QPushButton*>(sender());

    qDebug() << btn->text();
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
