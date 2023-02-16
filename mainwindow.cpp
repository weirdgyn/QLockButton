#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lockButton, &QLockButton::release,this,&MainWindow::onRelease);
    connect(ui->lockButton, &QLockButton::premature,this,&MainWindow::onPremature);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRelease()
{
    ui->lblStatus->setText("Released!");
}

void MainWindow::onPremature(int remainingTime)
{
    ui->lblStatus->setText("Too early");
}

