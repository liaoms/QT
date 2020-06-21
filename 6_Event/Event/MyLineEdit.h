#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr);

protected:
    bool event(QEvent* event);
    void keyPressEvent(QKeyEvent* event);

};

#endif // MYLINEEDIT_H
