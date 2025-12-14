#include "mainwindowuser.h"
#include "ui_mainwindowuser.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>

MainWindowUser::MainWindowUser(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowUser)
{
    ui->setupUi(this);
    ui->inventoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadInventory();
    QString imagePath = ":/images/LIBSPACE FT/1.png";
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull() && ui->LibSpaceLogo) {
        ui->LibSpaceLogo->setPixmap(pixmap);
        ui->LibSpaceLogo->setScaledContents(true);

    }
}

MainWindowUser::~MainWindowUser()
{
    delete ui;
}

void MainWindowUser::loadInventory()
{
    QFile file("database.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    ui->inventoryTable->setRowCount(0);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList p = line.split(";");
        if (p.size() != 4) continue;

        int r = ui->inventoryTable->rowCount();
        ui->inventoryTable->insertRow(r);

        ui->inventoryTable->setItem(r, 0, new QTableWidgetItem(p[0]));

        ui->inventoryTable->setItem(r, 3, new QTableWidgetItem(p[3]));

        ui->inventoryTable->setItem(r, 2, new QTableWidgetItem(p[2]));

        ui->inventoryTable->setItem(r, 1, new QTableWidgetItem(p[1]));

        for (int c = 0; c < 4; c++) {
            ui->inventoryTable->item(r,c)
            ->setFlags(ui->inventoryTable->item(r,c)->flags()
                       & ~Qt::ItemIsEditable);
        }

        QPushButton *btn = new QPushButton("Request");
        ui->inventoryTable->setCellWidget(r, 4, btn);

        connect(btn, &QPushButton::clicked,
                this, &MainWindowUser::handleRequest);
    }

    file.close();
}

void MainWindowUser::handleRequest()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    for (int r = 0; r < ui->inventoryTable->rowCount(); r++) {

        if (ui->inventoryTable->cellWidget(r,4) != btn)
            continue;

        QString status = ui->inventoryTable->item(r,3)->text();

        if (status == "Full") {
            QMessageBox::warning(
                this,
                "Gagal",
                "Status FULL, tidak bisa request"
                );
            return;
        }

        QFile file("request.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::critical(
                this,
                "Error",
                "Gagal menyimpan request"
                );
            return;
        }

        QTextStream out(&file);

        QString username = "libspaceuser";

        out << ui->inventoryTable->item(r,0)->text() << ";"
            << ui->inventoryTable->item(r,1)->text() << ";"
            << username << ";"
            << "waiting\n";

        file.close();

        QMessageBox::information(this, "OK", "Request berhasil dikirim");
        return;
    }
}

void MainWindowUser::on_listRequestButton_clicked()
{
    listrequest = new ListRequest(this);

    connect(listrequest, &ListRequest::backRequested,
            this, &MainWindowUser::showUser);

    listrequest->show();
    hide();
}

void MainWindowUser::on_infoRuanganButton_clicked()
{
    informasiruangan = new InformasiRuangan(this);

    connect(informasiruangan, &InformasiRuangan::backRequested,
            this, &MainWindowUser::showUser);

    informasiruangan->show();
    hide();
}

void MainWindowUser::showUser()
{
    show();
}

void MainWindowUser::on_logOutButton_clicked()
{
    emit logoutRequested();
    close();
}
