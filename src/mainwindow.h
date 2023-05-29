#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QWidget>


class MainWindow : public QFrame
{
public:
  explicit MainWindow(QWidget *parent = nullptr);

private:
  QFrame *topBar;
  QFrame *contentWidget;
  QFrame *bottomBar;

};
#endif // MAINWINDOW_H
