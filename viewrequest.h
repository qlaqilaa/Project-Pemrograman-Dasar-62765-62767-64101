#ifndef VIEWREQUEST_H
#define VIEWREQUEST_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewRequest;
}
QT_END_NAMESPACE

class ViewRequest : public QMainWindow
{
    Q_OBJECT

public:
    ViewRequest(QWidget *parent = nullptr);
    ~ViewRequest();

signals:
    void backRequested();

private slots:
    void loadRequest();
    void saveAll();
    void handleDelete();
    void on_backButton_clicked();

private:
    Ui::ViewRequest *ui;
};

#endif
