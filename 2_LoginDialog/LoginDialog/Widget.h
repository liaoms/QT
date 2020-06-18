#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <QWidget>
#include "QLoginDialog.h"

class Widget : public QWidget
{
    Q_OBJECT
private:

    Widget();

    bool construct();

public:
    static Widget* NewInstance();

    ~Widget();
};

#endif // __WIDGET_H__
