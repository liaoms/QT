
//UI类

#ifndef __CALCULATORUI_H__
#define __CALCULATORUI_H__

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

#include "ICalculator.h"

class CalculatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_pLineEdit;
    QPushButton* m_pButton[20];

    ICalculator * m_cal;    //接口类对象(要使用接口)

    CalculatorUI();

    bool construct();

private slots:
    void onButtonClicked();

public:

    static CalculatorUI* NewInstance();  //二阶构造模式生成对象
    void setCalculator(ICalculator* cal);   //设置接口
    ICalculator* getCalculator();           //返回使用的接口
    void show();
    ~CalculatorUI();
};

#endif // __CALCULATORUI_H__
