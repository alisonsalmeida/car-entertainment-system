#include <QStackedLayout>
#include "content.h"
#include "android-head-unit/aa_auto_widget.h"
#include "music-player/music_player.h"
#include "widget.h"


class BaseWidget: public IWidget {
public:
    explicit BaseWidget(QWidget *parent = nullptr): IWidget(parent){};
    virtual void on_focusin() const {};
    virtual void on_focusout() const {};
};


ContentWidget::ContentWidget(QWidget *parent)
  : QFrame(parent)
{
    this->slayout = new QStackedLayout();
    unsigned int length = sizeof(this->pages)/sizeof(this->pages[0]);
    QString colors[] = {"red", "green", "blue", "gray", "white"};

    for(unsigned int i = 0; i < length; i++){
        IWidget *page;

        if (i == 1) {
            page = new MusicPlayerWidget(this);
        }

        else if (i == 4) {
            page = new AAutoWidget(this);
        }

        else {
            page = new BaseWidget(this);
            QString color = "background-color: " + colors[i] + ";";
            page->setStyleSheet(color);
        }

        this->slayout->addWidget(page);
        this->pages[i] = page;
    }

    this->setLayout(this->slayout);
    this->slayout->setCurrentIndex(2);
}

void ContentWidget::changeWindow(unsigned int index) {
    this->slayout->setCurrentIndex(index);

    unsigned int length = sizeof(this->pages)/sizeof(this->pages[0]);
    for (unsigned int i; i < length; i++) {
        IWidget *p = this->pages[i];
        if (i == index) {
            p->on_focusin();
        } else {
            p->on_focusout();
        }
    }
}

void ContentWidget::resizeEvent(QResizeEvent *event) {
    unsigned int length = sizeof(this->pages)/sizeof(this->pages[0]);
    for (unsigned int i; i < length; i++){
        this->pages[i]->resize(event->size());
    }
}
