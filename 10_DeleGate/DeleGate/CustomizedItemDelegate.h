
//自定义委托类
#ifndef __CUSTOMIZEDITEMDELEGATE_H__
#define __CUSTOMIZEDITEMDELEGATE_H__

#include <QItemDelegate>

class CustomizedItemDelegate : public QItemDelegate
{
    Q_OBJECT

    mutable QModelIndex m_index;
protected slots:

    //关闭编辑器信号组件
    void onCloseEditor(QWidget* editor);
    //提交编辑器数据信号
    void onCommitData(QWidget* editor);
public:
    explicit CustomizedItemDelegate(QObject* parent = 0);

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
    //重写编辑器绘制函数
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // __CUSTOMIZEDITEMDELEGATE_H__
