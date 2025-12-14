#include "roominformation.h"
#include "ui_informasiruangan.h"
#include "ui_roominformation.h"
#include <QMainWindow>

RoomInformation::RoomInformation(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InformasiRuangan2)
{
    ui->setupUi(this);
    QString imagePath = "C:/Users/len0v0/Downloads/LIBSPACE FT/1.png";
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull() && ui->LibSpaceLogo) {
        ui->LibSpaceLogo->setPixmap(pixmap);
        ui->LibSpaceLogo->setScaledContents(true);

    }
}

RoomInformation::~RoomInformation()
{
    delete ui;
}
