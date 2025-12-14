#ifndef INFORMASIRUANGAN2_H
#define INFORMASIRUANGAN2_H
#include <QMainWindow>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class InformasiRuangan2; }
QT_END_NAMESPACE

class InformasiRuangan2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformasiRuangan2(QWidget *parent = nullptr);
    ~InformasiRuangan2();

private slots:
    void on_backButton_clicked();
    void loadImage(QLabel *label, const QString &path);

signals:
    void backRequested();

private:
    Ui::InformasiRuangan2 *ui;
};


#endif // INFORMASIRUANGAN_H
