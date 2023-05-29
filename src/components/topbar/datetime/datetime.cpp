#include "datetime.h"


DateTimeWidget::DateTimeWidget(QWidget *parent)
  :  QLabel(parent)
{
    this->setText("7:57 AM");
    this->setStyleSheet("color: white;");
}
