//
// Created by alison on 10/04/23.
//

#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <QWidget>
#include "src/components/content/widget.h"


class MusicPlayerWidget: public IWidget {

public:
    explicit MusicPlayerWidget(QWidget *parent = nullptr);

    virtual void on_focusin() const {};
    virtual void on_focusout() const {};
};


#endif //MUSIC_PLAYER_H
