
//接口类
#ifndef __ICALCULATOR_H__
#define __ICALCULATOR_H__

#include <QString>

class ICalculator
{
public:
    virtual bool expression(const QString& exp) = 0;    //设置表达式并计算结果
    virtual QString result() = 0;                       //返回结果
};


#endif // __ICALCULATOR_H__
