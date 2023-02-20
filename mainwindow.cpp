#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->lockButton, &QLockButton::success, this,
          &MainWindow::onCommuted);
  connect(ui->lockButton, &QLockButton::fail, this, &MainWindow::onFailed);

  ui->mode->setCurrentText(QLockButton::ModeToString(ui->lockButton->mode()));
  ui->status->setCurrentText(
      QLockButton::StatusToString(ui->lockButton->status()));

  ui->unlockTimeout->setValue(ui->lockButton->unlockTimeout());
  ui->lockTimeout->setValue(ui->lockButton->lockTimeout());
  ui->borderWidth->setValue(ui->lockButton->borderWidth());

  mColorDialog.setModal(false);
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

void MainWindow::on_borderColor_clicked()
{
    mColorDialog.setCurrentColor(ui->lockButton->borderColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->lockButton->setBorderColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_backgroundColor_clicked()
{
    mColorDialog.setCurrentColor(ui->lockButton->backgroundColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->lockButton->setBackgroundColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_innerColor_clicked()
{
    mColorDialog.setCurrentColor(ui->lockButton->innerColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->lockButton->setInnerColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}

