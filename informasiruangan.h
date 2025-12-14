#ifndef INFORMASIRUANGAN_H
#define INFORMASIRUANGAN_H
#include <QMainWindow>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class InformasiRuangan; }
QT_END_NAMESPACE

class InformasiRuangan : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformasiRuangan(QWidget *parent = nullptr);
    ~InformasiRuangan();

private slots:
    void on_backButton_clicked();
    void loadImage(QLabel *label, const QString &path);

signals:
    void backRequested();

private:
    Ui::InformasiRuangan *ui;
};


#endif // INFORMASIRUANGAN_H
