#ifndef ROOMINFORMATION_H
#define ROOMINFORMATION_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class InformasiRuangan2; }
QT_END_NAMESPACE

class RoomInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomInformation(QWidget *parent = nullptr);
    ~RoomInformation();

private slots:
    void on_backButton_clicked();

private:
    Ui::InformasiRuangan2 *ui;
};
#endif // ROOMINFORMATION_H
