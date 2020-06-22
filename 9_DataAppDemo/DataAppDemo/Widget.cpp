#include "Widget.h"
#include "ScoreInfo.h"
#include "DataSource.h"
#include <QMessageBox>
#include <QEvent>
#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 500);
    m_view.setParent(this);
    m_view.installEventFilter(this);

    m_refreshBtn.setParent(this);
    m_refreshBtn.setText("Refresh");

    m_clearBtn.setParent(this);
    m_clearBtn.setText("Clear");

    m_scoreBtn.setParent(this);
    m_scoreBtn.setText("Score");

    initUI();

    m_menu.addAction("Delete");



    m_model.setView(m_view);

    connect(&m_refreshBtn, SIGNAL(clicked()), this, SLOT(onRefreshBtnClicked()));
    connect(&m_clearBtn, SIGNAL(clicked()), this, SLOT(onClearBtnClicked()));
    connect(&m_scoreBtn, SIGNAL(clicked()), this, SLOT(onScoreBtnClicked()));
    connect(m_menu.actions()[0], SIGNAL(triggered()), this, SLOT(onDeleteActionClicked()));

    onRefreshBtnClicked();
}

void Widget::initUI()
{
    QHBoxLayout* hLayout = new QHBoxLayout();
    QVBoxLayout* vLayout = new QVBoxLayout();

    hLayout->addWidget(&m_refreshBtn);
    hLayout->addWidget(&m_clearBtn);
    hLayout->addWidget(&m_scoreBtn);


    vLayout->addWidget(&m_view, 5);
    vLayout->addLayout(hLayout, 1);

    setLayout(vLayout);
}

void Widget::onDeleteActionClicked()
{
    m_model.remove(m_view.currentIndex().row());
}

void Widget::onRefreshBtnClicked()
{
    DataSource ds;

    m_model.clear();

    if( ds.setDataPath( QDir::currentPath() + "/test.txt") )
    {
        m_model.add(ds.fetchData());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Data source read error!", QMessageBox::Ok);
    }
}

void Widget::onClearBtnClicked()
{
    m_model.clear();
}

void Widget::onScoreBtnClicked()
{
    int min = 256;
    int max = 0;
    int average = 0;

    if( m_model.count() > 0 )
    {
        for(int i=0; i<m_model.count(); i++)
        {
            ScoreInfo info = m_model.getItem(i);

            if( info.score() < min )
            {
                min = info.score();
            }

            if( info.score() > max )
            {
                max = info.score();
            }

            average += info.score();
        }

        average /= m_model.count();

        QMessageBox::information(this, "Statistic", QString().sprintf("Min: %d\nMax: %d\nAverage: %d", min, max, average), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, "Statistic", "No data record!", QMessageBox::Ok);
    }
}

bool Widget::eventFilter(QObject* obj, QEvent* evt)
{
    if( (obj == &m_view) && (evt->type() == QEvent::ContextMenu) )
    {
        m_menu.exec(cursor().pos());
    }

    return QWidget::eventFilter(obj, evt);
}

Widget::~Widget()
{
    
}
