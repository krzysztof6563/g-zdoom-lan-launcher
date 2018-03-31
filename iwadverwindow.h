#ifndef IWADVERWINDOW_H
#define IWADVERWINDOW_H

#include <QDialog>
#include "config.h"

namespace Ui {
class IWADVerWindow;
}

class IWADVerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IWADVerWindow(Config *c, QWidget *parent = 0);
    ~IWADVerWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IWADVerWindow *ui;

    Config *config;
};

#endif // IWADVERWINDOW_H
