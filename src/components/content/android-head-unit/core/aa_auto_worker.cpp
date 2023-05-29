#include "aa_auto_worker.h"
#include "aa_auto.h"


AAutoWorker::AAutoWorker(QFrame *widget, AAController *controller)
  : QObject(nullptr)
{
    this->_widget = widget;
    this->controller = controller;
    this->aa_auto_service = new AAutoService(widget);
}

void AAutoWorker::runAAServive()
{   
    this->aa_auto_service->start(this->controller);
}