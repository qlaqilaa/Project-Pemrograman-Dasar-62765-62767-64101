#ifndef LISTREQUEST_H
#define LISTREQUEST_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ListRequest; }
QT_END_NAMESPACE

class ListRequest : public QMainWindow
{
    Q_OBJECT
public:
    explicit ListRequest(QWidget *parent = nullptr);
    ~ListRequest();

private slots:
    void on_backButton_clicked();
    void loadRequest();
    void handleDelete();
    void saveAll();

signals:
    void backRequested();

private:
    Ui::ListRequest *ui;
};

#endif
