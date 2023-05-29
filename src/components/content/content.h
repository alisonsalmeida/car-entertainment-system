#ifndef CONTENT_H
#define CONTENT_H

#include <QFrame>
#include <QStackedLayout>
#include "widget.h"

class ContentWidget: public QFrame {
Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = nullptr);

public slots:

    void changeWindow(unsigned int index);

private:
    IWidget *pages[5];
    QStackedLayout *slayout;

    virtual void resizeEvent(QResizeEvent *event) override;
};
#endif
