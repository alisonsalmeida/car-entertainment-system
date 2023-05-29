#ifndef BOTTOM_BAR_H
#define BOTTOM_BAR_H

#include <QFrame>
#include <QWidget>
#include "button/button.h"

class BottomBarWidget: public QFrame
{
    Q_OBJECT
public:
    explicit BottomBarWidget(QWidget *parent = nullptr);

private slots:
    void handleButton(unsigned int index);

private:
    Button *buttons[5];

signals:
    void changeButtonSelected(unsigned int index);
};

#endif
