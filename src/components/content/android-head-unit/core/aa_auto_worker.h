#ifndef AA_AUTO_WORKER_H
#define AA_AUTO_WORKER_H

#include <QThread>
#include <QFrame>
#include "aa_auto.h"
#include "src/components/content/android-head-unit/aa_auto_controller.h"

class AAutoWorker: public QObject
{
    Q_OBJECT

public:
    explicit AAutoWorker(QFrame *widget, AAController *controller);

private:
    QFrame *_widget;
    AAutoService *aa_auto_service;
    AAController *controller = nullptr;

signals:
    void aa_connect();
    void aa_disconnect();

public slots:
    void runAAServive();
};

#endif
