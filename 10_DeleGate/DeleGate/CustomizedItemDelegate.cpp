#include "CustomizedItemDelegate.h"
#include <QDebug>
#include <QItemDelegate>
#include <QModelIndex>
#include <QComboBox>
#include <QCheckBox>

CustomizedItemDelegate::CustomizedItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
    connect(this, SIGNAL(closeEditor(QWidget*)), this, SLOT(onCloseEditor(QWidget*)));
    connect(this, SIGNAL(commitData(QWidget*)), this, SLOT(onCommitData(QWidget*)));
}

QWidget* CustomizedItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "CustomizedItemDelegate::createEditor";

    QWidget* ret = NULL;

    m_index = index;

    if( index.data().type() == QVariant::Bool )   //根据选择编辑项的类型，创建不同的编辑器组件
    {
        QCheckBox* cb = new QCheckBox(parent);

        cb->setText("Check to TRUE");

        ret = cb;
    }
    else if( index.data().type() == QVariant::Char )
    {
        QComboBox* cb = new QComboBox(parent);

        cb->addItem("A");
        cb->addItem("B");
        cb->addItem("C");
        cb->addItem("D");

        ret = cb;
    }
    else
    {
        ret = QItemDelegate::createEditor(parent, option, index);
    }

    return ret;
}

void CustomizedItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "CustomizedItemDelegate::updateEditorGeometry";

    editor->setGeometry(option.rect);
}

void CustomizedItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if( index.data().type() == QVariant::Bool )
    {
        QCheckBox* cb = dynamic_cast<QCheckBox*>(editor);

        if( cb != NULL )
        {
            cb->setChecked(index.data().toBool());
        }
    }
    else if( index.data().type() == QVariant::Char )
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);

        if( cb != NULL )
        {
            for(int i=0; i<cb->count(); i++)
            {
                if( cb->itemText(i) == index.data().toString() )
                {
                    cb->setCurrentIndex(i);
                    break;
                }
            }
        }
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void CustomizedItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug() << "CustomizedItemDelegate::setModelData";

    if( index.data().type() == QVariant::Bool )
    {
        QCheckBox* cb = dynamic_cast<QCheckBox*>(editor);

        if( cb != NULL )
        {
            model->setData(index, cb->isChecked(), Qt::DisplayRole);
        }
    }
    else if( index.data().type() == QVariant::Char )
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);

        if( cb != NULL )
        {
            model->setData(index, cb->currentText().at(0), Qt::DisplayRole);
        }
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}

void CustomizedItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if( m_index != index )
    {
        QItemDelegate::paint(painter, option, index);
    }
}

void CustomizedItemDelegate::onCloseEditor(QWidget* editor)
{
    qDebug() << "CustomizedItemDelegate::onCloseEditor";
    m_index = QModelIndex();
}

void CustomizedItemDelegate::onCommitData(QWidget* editor)
{
    qDebug() << "CustomizedItemDelegate::onCommitData";
}
