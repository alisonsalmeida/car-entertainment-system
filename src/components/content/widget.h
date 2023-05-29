//
// Created by alison on 26/04/23.
//

#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include <QWidget>


class IWidget: public QFrame {
public:
    explicit IWidget(QWidget *parent=nullptr) : QFrame(parent) {};
    virtual void on_focusin() const = 0;
    virtual void on_focusout() const = 0;
    bool inFocus = false;

};

#endif //WIDGET_H
