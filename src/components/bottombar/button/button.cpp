#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "button.h"


Button::Button(unsigned int index, QString icon_name, QWidget *parent)
    : QFrame(parent)
{   
    this->_index = index;
    this->_icon_name = icon_name;

    // por default o icone é nao selecionado
    this->_icon = new QLabel(this);
    this->select(false);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(this->_icon);

    this->setLayout(hlayout);
    this->_icon->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
}

void Button::select(bool value) {
    // troca a cor de fundo
    QString color = value == true ? "background-color: #2E3069;" : "background-color: #040410;";
    this->setStyleSheet(color);

    //troca o icone para nao selecionado
    QString suffix = value == true ? "selected" : "unselected";
    QString icon_path = "assets/icons/" + this->_icon_name + "_" + suffix + ".png";
    this->_icon->setPixmap(QPixmap(icon_path));
}
