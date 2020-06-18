
//UI与业务逻辑关联类

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "CalculatorUI.h"
#include "QCalculatorDec.h"

class Calculator
{
private:
    CalculatorUI* m_ui;
    QCalculatorDec m_cal;

    Calculator();

    bool construct();

public:
    static Calculator* NewInstance();

    void show();

    ~Calculator();
};

#endif // CALCULATOR_H
