#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qlockbutton/qlockbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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

private:
    Ui::MainWindow *ui;

    void onCommuted(QLockButton::Status status);
    void onFailed(int remainingTime);
};
#endif // MAINWINDOW_H
