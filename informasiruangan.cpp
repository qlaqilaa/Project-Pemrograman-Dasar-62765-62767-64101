#include "informasiruangan.h"
#include "ui_informasiruangan.h"

#include <QMainWindow>

InformasiRuangan::InformasiRuangan(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InformasiRuangan)
{
    ui->setupUi(this);
    loadImage(ui->LibSpaceLogo, ":/images/LIBSPACE FT/1.png");
    loadImage(ui->meetingRoom, ":/images/LIBSPACE FT/3.png");
    loadImage(ui->discussionRoom, ":/images/LIBSPACE FT/4.png");


}

InformasiRuangan::~InformasiRuangan()
{
    delete ui;
}

void::InformasiRuangan::on_backButton_clicked()
{
    emit backRequested();
    close();
}

void InformasiRuangan::loadImage(QLabel *label, const QString &path)
{
    if (!label) return;

    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        label->setPixmap(pixmap);
        label->setScaledContents(true);
    }
}
