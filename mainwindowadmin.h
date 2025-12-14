#ifndef MAINWINDOWADMIN_H
#define MAINWINDOWADMIN_H

#include "informasiruangan2.h"
#include "viewrequest.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowAdmin;
}
QT_END_NAMESPACE

class MainWindowAdmin : public QMainWindow {
    Q_OBJECT

public:
    MainWindowAdmin(QWidget *parent = nullptr);
    ~MainWindowAdmin();

signals:
    void logoutRequested();

private slots:
    void addRow(
        const QString& id,
        int lantai,
        const QString& peminjam,
        const QString& status
        );
    void on_viewRequestButton_clicked();
    void on_logOutButton_clicked();
    void on_addListButton_clicked();
    void handleComboChanged(const QString &value);
    void handleRemoveButton();
    void saveToTxt(const QString &filename);
    void loadFromTxt(const QString &filename);
    void showAdmin();
    void on_infoRuanganButton_clicked();

private:
    Ui::MainWindowAdmin *ui;
    ViewRequest *viewrequest = nullptr;
    InformasiRuangan2 *informasiruangan = nullptr;

};

#endif
