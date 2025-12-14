#include "informasiruangan2.h"
#include "ui_informasiruangan2.h"

#include <QMainWindow>

InformasiRuangan2::InformasiRuangan2(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InformasiRuangan2)
{
    ui->setupUi(this);
    loadImage(ui->LibSpaceLogo,":/images/LIBSPACE FT/1.png");
    loadImage(ui->meetingRoom, ":/images/LIBSPACE FT/3.png");
    loadImage(ui->discussionRoom, ":/images/LIBSPACE FT/4.png");
}

InformasiRuangan2::~InformasiRuangan2()
{
    delete ui;
}

void::InformasiRuangan2::on_backButton_clicked()
{
    emit backRequested();
    close();
}

void InformasiRuangan2::loadImage(QLabel *label, const QString &path)
{
    if (!label) return;

    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        label->setPixmap(pixmap);
        label->setScaledContents(true);
    }
}
