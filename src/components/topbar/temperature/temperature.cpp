#include "temperature.h"


TemperatureWidget::TemperatureWidget(QWidget *parent)
  :  QLabel(parent)
{
    this->setText("21°");
    this->setStyleSheet("color: white;");
}
