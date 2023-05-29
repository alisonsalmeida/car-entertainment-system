#ifndef DATETIME_H
#define DATETIME_H

#include <QLabel>
#include <QWidget>


class DateTimeWidget : public QLabel
{
public:
    explicit DateTimeWidget(QWidget *parent = nullptr);
    
};

#endif
