#include "mainwindowadmin.h"
#include "ui_mainwindowadmin.h"
#include "viewrequest.h"
#include <QComboBox>
#include <QSpinBox>
#include <QFile>
#include <QTextStream>
#include <qtablewidget.h>

MainWindowAdmin::MainWindowAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowAdmin)
{
    ui->setupUi(this);
    loadFromTxt("database.txt");
    QString imagePath = ":/images/LIBSPACE FT/1.png";
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull() && ui->LibSpaceLogo) {
        ui->LibSpaceLogo->setPixmap(pixmap);
        ui->LibSpaceLogo->setScaledContents(true);

    }
}

MainWindowAdmin::~MainWindowAdmin()
{
    delete ui;
}

void MainWindowAdmin::addRow(
    const QString& id,
    int lantai,
    const QString& peminjam,
    const QString& status
    )
{
    QTableWidget *table = ui->inventoryTable;
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 0, new QTableWidgetItem(id));

    table->setItem(row, 1, new QTableWidgetItem(QString::number(lantai)));

    table->setItem(row, 2, new QTableWidgetItem(peminjam));

    QComboBox *combo = new QComboBox();
    combo->addItems({"Kosong", "Full"});
    combo->setCurrentText(status);
    table->setCellWidget(row, 3, combo);

    QPushButton *btn = new QPushButton("Hapus");
    table->setCellWidget(row, 4, btn);

    connect(btn, &QPushButton::clicked,
            this, &MainWindowAdmin::handleRemoveButton);
}

void MainWindowAdmin::handleComboChanged(const QString &value)
{
    QTableWidget *table = ui->inventoryTable;
    QComboBox *combo = qobject_cast<QComboBox*>(sender());
    if (!combo) return;

    for (int r = 0; r < table->rowCount(); ++r)
    {
        if (table->cellWidget(r, 3) == combo)
        {
            qDebug() << "Baris" << r << "status berubah menjadi" << value;
            return;
        }
    }
}

void MainWindowAdmin::handleRemoveButton()
{
    QTableWidget *table = ui->inventoryTable;
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    for (int r = 0; r < table->rowCount(); ++r)
    {
        if (table->cellWidget(r, 4) == btn)
        {
            table->removeRow(r);
            qDebug() << "Baris" << r << "dihapus!";
            return;
        }
    }
}

void MainWindowAdmin::on_addListButton_clicked()
{
    addRow("", 2, "", "Kosong");
}


void MainWindowAdmin::saveToTxt(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    QTableWidget *table = ui->inventoryTable;

    for (int r = 0; r < table->rowCount(); r++)
    {
        QString id       = table->item(r,0)->text();
        int lantai       = table->item(r,1)->text().toInt();
        QString peminjam = table->item(r,2)->text();

        QComboBox *combo = qobject_cast<QComboBox*>(table->cellWidget(r,3));
        QString status   = combo ? combo->currentText() : "";

        out << id << ";" << lantai << ";" << peminjam << ";" << status << "\n";
    }
}



void MainWindowAdmin::loadFromTxt(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    ui->inventoryTable->setRowCount(0);
    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList p = line.split(";");
        if (p.size() != 4) continue;

        QString id       = p[0];
        int lantai       = p[1].toInt();
        QString peminjam = p[2];
        QString status   = p[3];

        addRow(id, lantai, peminjam, status);
    }
}

void MainWindowAdmin::on_infoRuanganButton_clicked()
{
    informasiruangan = new InformasiRuangan2(this);

    connect(informasiruangan, &InformasiRuangan2::backRequested,
            this, &MainWindowAdmin::showAdmin);

    informasiruangan->show();
    hide();
}



void MainWindowAdmin::on_logOutButton_clicked()
{
    saveToTxt("database.txt");
    emit logoutRequested();
    close();
}

void MainWindowAdmin::on_viewRequestButton_clicked()
{
    viewrequest = new ViewRequest(this);

    connect(viewrequest, &ViewRequest::backRequested,
            this, &MainWindowAdmin::showAdmin);

    viewrequest->show();
    hide();
}

void MainWindowAdmin::showAdmin()
{
    show();
}
