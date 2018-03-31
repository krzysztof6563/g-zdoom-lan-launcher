#ifndef IWADVERWINDOW_H
#define IWADVERWINDOW_H

#include <QDialog>

namespace Ui {
class IWADVerDialog;
}

class IWADVerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IWADVerDialog(Config *c, QWidget *parent = 0);
    ~IWADVerDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IWADVerDialog *ui;
};

#endif // IWADVERWINDOW_H
