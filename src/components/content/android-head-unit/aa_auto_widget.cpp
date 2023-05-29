//
// Created by alison on 03/04/23.
//
#include <QFrame>
#include "aa_auto_widget.h"
#include "src/components/content/widget.h"


AAutoWidget::AAutoWidget(QWidget *parent): IWidget(parent)
{
    this->controller = new AAController();
    worker = new AAutoWorker(this, controller);
    thread = new QThread();

    connect(thread, &QThread::started, worker, &AAutoWorker::runAAServive);
    worker->moveToThread(thread);
    thread->start();
}

void AAutoWidget::resizeEvent(QResizeEvent *event) {
    // reajusta a tela de renderização do android auto
    QSize size = event->size();
    this->controller->aa_set_render_rectangle(0, 0, size.width(), size.height());
}

void AAutoWidget::mousePressEvent(QMouseEvent *event) {
    qDebug("mouse press event: %d, %d", event->x(), event->y());
    this->controller->aa_mouse_press_event(event->x(), event->y());
}

void AAutoWidget::mouseReleaseEvent(QMouseEvent *event) {
    qDebug("mouse release event: %d, %d", event->x(), event->y());
    this->controller->aa_mouse_release_event(event->x(), event->y());
}

void AAutoWidget::mouseMoveEvent(QMouseEvent *event) {
    qDebug("mouse move event: %d, %d", event->x(), event->y());
    this->controller->aa_mouse_move_event(event->x(), event->y());
}

void AAutoWidget::on_focusin() const {
    qDebug("focus in aa_auto_controller");
    this->controller->aa_set_state_player(true);
}

void AAutoWidget::on_focusout() const {
    qDebug("focus out aa_auto_controller");
    this->controller->aa_set_state_player(false);
}