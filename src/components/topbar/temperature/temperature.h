#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QLabel>
#include <QWidget>


class TemperatureWidget : public QLabel
{
public:
    explicit TemperatureWidget(QWidget *parent = nullptr);
    
};

#endif
