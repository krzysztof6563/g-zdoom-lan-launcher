#include "iwadverwindow.h"
#include "ui_iwadverwindow.h"

IWADVerWindow::IWADVerWindow(Config *c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IWADVerWindow),
    config(c)
{
    ui->setupUi(this);
}

IWADVerWindow::~IWADVerWindow()
{
    delete ui;
}

void IWADVerWindow::on_pushButton_clicked()
{
    if (ui->radioButtonDoom->isChecked()) {
        config->setIWADVer(1);
    } else {
        config->setIWADVer(2);
    }
    this->close();
}
