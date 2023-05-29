#ifndef AA_AUTO_WIDGET_H
#define AA_AUTO_WIDGET_H

#include <QFrame>
#include <QWidget>
#include <QThread>
#include <QResizeEvent>
#include <QMediaPlayer>
#include "core/aa_auto_worker.h"
#include "aa_auto_controller.h"
#include "src/components/content/widget.h"

class AAutoWidget: public IWidget
{
    Q_OBJECT

public:
    AAutoWorker *worker;
    QThread *thread;
    bool started = false;
    AAController *controller = nullptr;

    explicit AAutoWidget(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void on_focusin() const override;
    virtual void on_focusout() const override;
};

#endif
