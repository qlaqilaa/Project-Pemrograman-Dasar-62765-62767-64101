#ifndef MAINWINDOWUSER_H
#define MAINWINDOWUSER_H
#include <QMainWindow>
#include "informasiruangan.h"
#include "listrequest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowUser; }
QT_END_NAMESPACE

class MainWindowUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowUser(QWidget *parent = nullptr);
    ~MainWindowUser();

signals:
    void logoutRequested();
    void backRequested();

private slots:
    void handleRequest();
    void on_listRequestButton_clicked();
    void on_logOutButton_clicked();
    void showUser();
    void on_infoRuanganButton_clicked();

private:
    Ui::MainWindowUser *ui;
    ListRequest *listrequest = nullptr;
    InformasiRuangan *informasiruangan = nullptr;
    void loadInventory();
};

#endif
