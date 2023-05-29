#include <QFrame>
#include <QWidget>
#include <QHBoxLayout>

#include "topbar.h"
#include "datetime/datetime.h"
#include "temperature/temperature.h"


TopBarWidget::TopBarWidget(QWidget *parent)
    : QFrame(parent)
{
    QHBoxLayout *hlayout = new QHBoxLayout();
    DateTimeWidget *datetimeWidget = new DateTimeWidget(this);
    TemperatureWidget *temperatureWidget = new TemperatureWidget(this);
    
    QString style = QString(
        "background-color: #2b2d6b;"
    );

    this->setStyleSheet(style);
    
    hlayout->addStretch(10);
    hlayout->addWidget(datetimeWidget, 80);
    hlayout->addWidget(temperatureWidget, 10);
    hlayout->setSpacing(0);
    
    datetimeWidget->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);

    this->setLayout(hlayout);
}
