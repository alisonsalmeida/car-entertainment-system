#include <QVBoxLayout>
#include <QFrame>
#include "mainwindow.h"
#include "src/components/topbar/topbar.h"
#include "src/components/bottombar/bottombar.h"
#include "src/components/content/content.h"

#include <QRadialGradient>
#include <QPainter>
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
  : QFrame(parent)
{

  this->topBar = new TopBarWidget(this);

  ContentWidget *contentWidget = new ContentWidget(this);
  this->contentWidget = contentWidget;

  BottomBarWidget *bottomBar = new BottomBarWidget(this);
  this->bottomBar = bottomBar;
  connect(bottomBar, &BottomBarWidget::changeButtonSelected, contentWidget, &ContentWidget::changeWindow);

  QVBoxLayout *vlayout = new QVBoxLayout();
  vlayout->addWidget(this->topBar, 5);
  vlayout->addWidget(this->contentWidget, 85);
  vlayout->addWidget(this->bottomBar, 10);
  vlayout->setSpacing(0);
  vlayout->setContentsMargins(0, 0, 0, 0);

  this->setLayout(vlayout);
  this->setGeometry(0, 0, 1024, 600);
  this->show();

}
