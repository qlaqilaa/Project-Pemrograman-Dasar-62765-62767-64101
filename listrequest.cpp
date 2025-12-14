#include "listrequest.h"
#include "ui_listrequest.h"
#include <QMainWindow>
#include <QFile>
#include <QTextStream>

ListRequest::ListRequest(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ListRequest)
{
    ui->setupUi(this);
    loadRequest();
    QString imagePath = ":/images/LIBSPACE FT/1.png";
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull() && ui->LibSpaceLogo) {
        ui->LibSpaceLogo->setPixmap(pixmap);
        ui->LibSpaceLogo->setScaledContents(true);

    }
}

ListRequest::~ListRequest()
{
    delete ui;
}

void ListRequest::loadRequest()
{
    QFile file("request.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    ui->inventoryTable->setRowCount(0);

    while (!in.atEnd()) {
        QStringList p = in.readLine().split(";");
        if (p.size() < 4) continue;

        int r = ui->inventoryTable->rowCount();
        ui->inventoryTable->insertRow(r);

        for (int i = 0; i < 4; i++) {
            QTableWidgetItem *item = new QTableWidgetItem(p[i]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->inventoryTable->setItem(r, i, item);
        }
        QPushButton *btn = new QPushButton("Hapus");
        ui->inventoryTable->setCellWidget(r, 4, btn);
        connect(btn, &QPushButton::clicked,
                this, &ListRequest::handleDelete);
    }
}

void ListRequest::handleDelete()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    for (int r=0; r<ui->inventoryTable->rowCount(); r++) {
        if (ui->inventoryTable->cellWidget(r,4) == btn) {
            ui->inventoryTable->removeRow(r);
            saveAll();
            return;
        }
    }
}

void ListRequest::saveAll()
{
    QFile file("request.txt");
    QTextStream out(&file);

    for (int r=0; r<ui->inventoryTable->rowCount(); r++) {
        out << ui->inventoryTable->item(r,0)->text() << ";"
            << ui->inventoryTable->item(r,1)->text() << ";"
            << ui->inventoryTable->item(r,2)->text() << ";"
            << ui->inventoryTable->item(r,3)->text() << "\n";
    }
}

void::ListRequest::on_backButton_clicked()
{
    emit backRequested();
    close();
}

