#include <QHBoxLayout>
#include "bottombar.h"
#include "button/button.h"

using namespace std;


BottomBarWidget::BottomBarWidget(QWidget *parent)
    : QFrame(parent)
{

    QHBoxLayout *vlayout = new QHBoxLayout();
    QString names[] = {"car_ok", "music", "home", "settings", "explore"};
    unsigned int length = sizeof(this->buttons)/sizeof(this->buttons[0]);

    for(unsigned int i = 0; i < length; i++){
        Button *button = new Button(i, names[i], this);
        connect(button, &Button::onClick, this, &BottomBarWidget::handleButton);
        vlayout->addWidget(button);

        if (i == 2){
            button->select(true);
        }
        this->buttons[i] = button;
    }
    
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vlayout);
}

void BottomBarWidget::handleButton(unsigned int index) {
    unsigned int length = sizeof(this->buttons)/sizeof(this->buttons[0]);
    
    for(unsigned int i = 0; i < length; i++){
        Button *button = this->buttons[i];
        if (i == index) {
            button->select(true);
        }
        else{
            button->select(false);
        }
    }

    emit this->changeButtonSelected(index);
}
