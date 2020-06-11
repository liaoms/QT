#ifndef __CALCULATORUI_H__
#define __CALCULATORUI_H__

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class CalculatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_pLineEdit;
    QPushButton* m_pButton[20];

    CalculatorUI();

    bool construct();

private slots:
    void onButtonClicked();

public:

    static CalculatorUI* NewInstance();  //二阶构造模式生成对象
    void show();
    ~CalculatorUI();
};

#endif // __CALCULATORUI_H__
