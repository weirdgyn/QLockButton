#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->lockButton, &QLockButton::commuted, this,
          &MainWindow::onCommuted);
  connect(ui->lockButton, &QLockButton::failed, this, &MainWindow::onFailed);

  ui->mode->setCurrentText(QLockButton::ModeToString(ui->lockButton->mode()));
  ui->status->setCurrentText(
      QLockButton::StatusToString(ui->lockButton->status()));

  ui->unlockTimeout->setValue(ui->lockButton->unlockTimeout());
  ui->lockTimeout->setValue(ui->lockButton->lockTimeout());
  ui->borderWidth->setValue(ui->lockButton->borderWidth());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onCommuted(QLockButton::Status status) {
  ui->lblStatus->setText(QLockButton::StatusToString(status));
}

void MainWindow::onFailed(int remainingTime) {
  ui->lblStatus->setText(QString("Too early: %0").arg(remainingTime));
}

void MainWindow::on_unlockTimeout_textChanged(const QString &arg1) {
  ui->lockButton->setUnlockTimeout(arg1.toInt());
}

void MainWindow::on_lockTimeout_textChanged(const QString &arg1) {
  ui->lockButton->setLockTimeout(arg1.toInt());
}

void MainWindow::on_status_currentTextChanged(const QString &arg1) {
  ui->lockButton->setStatus(QLockButton::StringToStatus(arg1));
}

void MainWindow::on_mode_currentTextChanged(const QString &arg1) {
  ui->lockButton->setMode(QLockButton::StringToMode(arg1));
  ui->lockButton->reset();
}

void MainWindow::on_borderWidth_textChanged(const QString &arg1) {
  ui->lockButton->setBorderWidth(arg1.toInt());
}
