
//业务实现类
#ifndef __CALCULATORCORE_H_
#define __CALCULATORCORE_H__

#include <QString>
#include <QStack>
#include <QQueue>

#include "ICalculator.h"

//业务类继承并实现接口
class QCalculatorDec : public ICalculator
{
protected:
    QString m_exp;
    QString m_result;

    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);
    bool match(QQueue<QString>& exp);
    QString calculate(QQueue<QString>& exp);
    QString calculate(QString l, QString op, QString r);
    bool transform(QQueue<QString>& exp, QQueue<QString>& output);
    QQueue<QString> split(const QString& exp);
public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool expression(const QString& exp);    //实现接口
    QString expression();
    QString result();                       //实现接口
};

#endif
