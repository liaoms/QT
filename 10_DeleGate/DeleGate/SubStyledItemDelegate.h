
//自定义委托类
#ifndef __SUBSTYLEDITEMDELEGATE_H__
#define __SUBSTYLEDITEMDELEGATE_H__

#include <QStyledItemDelegate>

class SubStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
protected slots:

    //关闭编辑器信号组件
    void onCloseEditor(QWidget* editor);
    //提交编辑器数据信号
    void onCommitData(QWidget* editor);
public:
    explicit SubStyledItemDelegate(QObject* parent = 0);

    /*
     * 重写委托关键成员函数，点击视图编辑数据时，该组成员函数会被调用
     */

    //重写创建编辑器组件
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //重写更新编辑器组件大小
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //重写通过索引从模型中获取数据到编辑器中
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //重写将编辑器数据写到模型中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // __SUBSTYLEDITEMDELEGATE_H__
