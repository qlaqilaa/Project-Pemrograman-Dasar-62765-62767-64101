#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "mainwindowadmin.h"
#include "mainwindowuser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_logInButton_clicked();
    void showLogin();

private:
    Ui::MainWindow *ui;
    MainWindowUser *mainwindowuser = nullptr;
    MainWindowAdmin *mainwindowadmin = nullptr;
};

#endif
