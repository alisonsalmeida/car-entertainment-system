//
// Created by alison on 10/04/23.
//

#include "music_player.h"
#include "src/components/content/widget.h"
#include <QString>


MusicPlayerWidget::MusicPlayerWidget(QWidget *parent): IWidget(parent)
{

    qDebug("music player");
    QString color = "background-color: red;";
    this->setStyleSheet(color);
}