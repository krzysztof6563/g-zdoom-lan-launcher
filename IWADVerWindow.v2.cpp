#include "IWADVerWindow.h"
#include "ui_IWADVerWindow.h"

IWADVerDialog::IWADVerDialog(Config *c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IWADVerDialog),
    config(c)
{
    ui->setupUi(this);
}

IWADVerDialog::~IWADVerDialog()
{
    delete ui;
}

void IWADVerDialog::on_pushButton_clicked()
{
    if (ui->radioButtonDoom->isChecked()) {
        c->setIWADVer(1);
    } else {
        c->setIWADVer(2);
    }
    this->close();
}
