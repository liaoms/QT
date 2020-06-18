#include "Calculator.h"

Calculator::Calculator()
{
    m_ui = NULL;
}


bool Calculator::construct()
{
    bool ret = true;
    m_ui = CalculatorUI::NewInstance();

    if(!m_ui)
    {
        ret = false;
    }
    else
    {
        m_ui->setCalculator(&m_cal);   //界面设置使用的接口
    }

    return ret;
}


Calculator* Calculator::NewInstance()
{
    Calculator* ret = new Calculator();

    if( (NULL == ret) || (!ret->construct()) )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void Calculator::show()
{
    m_ui->show();
}

Calculator::~Calculator()
{
    delete m_ui;
}
