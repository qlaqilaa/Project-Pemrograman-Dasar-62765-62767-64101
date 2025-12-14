#include "viewrequest.h"
#include "ui_viewrequest.h"
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QMainWindow>

ViewRequest::ViewRequest(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViewRequest)
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

ViewRequest::~ViewRequest()
{
    delete ui;
}

void ViewRequest::loadRequest()
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
                this, &ViewRequest::handleDelete);
    }
}

void ViewRequest::handleDelete()
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

void ViewRequest::saveAll()
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

void ViewRequest::on_backButton_clicked()
{
    emit backRequested();
    close();
}
