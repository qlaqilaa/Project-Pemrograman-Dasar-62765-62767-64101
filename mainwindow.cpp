#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindowadmin.h"
#include "mainwindowuser.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString imagePath = ":/images/LIBSPACE FT/2.png";
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull() && ui->LibSpaceLogo) {
        ui->LibSpaceLogo->setPixmap(pixmap);
        ui->LibSpaceLogo->setScaledContents(true);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logInButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QString user_valid = "libspaceuser";
    QString passuser_valid = "user123";
    QString admin_valid = "libspaceadmin";
    QString passadmin_valid = "admin123";

    if (username == admin_valid && password == passadmin_valid)
    {
        QMessageBox::information(this, "Login Berhasil",
                                 "Selamat datang, admin " + admin_valid + "!");
        hide();
        mainwindowadmin = new MainWindowAdmin(this);
        mainwindowadmin->show();
        connect(mainwindowadmin, &::MainWindowAdmin::layout, this, &QMainWindow::show);
        mainwindowadmin->show();
    }

    else if(username == user_valid && password == passuser_valid){
        QMessageBox::information(this, "Login Berhasil",
                                 "Selamat datang, user " + user_valid + "!");
        hide();
        mainwindowuser = new MainWindowUser(this);
        mainwindowuser ->show();
        connect(mainwindowuser, &::MainWindowUser::layout, this, &QMainWindow::show);
        mainwindowuser->show();

    }
    else
    {
        QMessageBox::warning(this, "Login Gagal",
                             "Username atau Password salah. Silakan coba lagi.");
    }
}

void MainWindow::showLogin()
{
    show();
}
