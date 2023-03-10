#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>

#include "qlockbutton/qlockbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_unlockTimeout_textChanged(const QString &arg1);

  void on_lockTimeout_textChanged(const QString &arg1);

  void on_status_currentTextChanged(const QString &arg1);

  void on_mode_currentTextChanged(const QString &arg1);

  void on_borderWidth_textChanged(const QString &arg1);

  void on_borderColor_clicked();

  void on_backgroundColor_clicked();

  void on_innerColor_clicked();

  void on_fillStartColor_clicked();

  void on_fillEndColor_clicked();

private:
  Ui::MainWindow *ui;
  QColorDialog mColorDialog;
  void onSuccess(QLockButton::Status status);
  void onFail(int remainingTime);
  void onAngleChanged(int angle);

#ifdef Q_OS_LINUX
  void beep();
#endif
};
#endif // MAINWINDOW_H
