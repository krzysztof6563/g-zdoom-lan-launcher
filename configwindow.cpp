#include "configwindow.h"
#include "ui_configwindow.h"

#include <iostream>

ConfigWindow::ConfigWindow(Config *c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow),
    config(c)
{
    ui->setupUi(this);
    ui->lineEditGameDir->insert(c->getGameLocation());
    ui->lineEditGameEnigne->insert(c->getEngineLocation());
    ui->lineEditBrutalDoom->insert(c->getBrutalDoomLocation());
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::on_pushButtonGameEngine_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Wskaż silink gry"), "",
            tr("All Files (*)"));
    ui->lineEditGameEnigne->setText(fileName);
}

void ConfigWindow::on_pushButtonGameDir_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,
            tr("Wskaż folder z plikami WAD"), ".",
             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditGameDir->setText(fileName+"/");
}

void ConfigWindow::on_buttonOk_clicked(QAbstractButton *button)
{
    if (button == ui->buttonOk->button(QDialogButtonBox::Ok)) {
        config->setEngineLocation(ui->lineEditGameEnigne->text());
        config->setGameLocation(ui->lineEditGameDir->text());
        config->setBrutalDoomLocation(ui->lineEditBrutalDoom->text());
        config->saveConfig();
    }
}

void ConfigWindow::on_pushButtonBrutalDoom_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Wskaż plik BrutalDoom"), "",
            tr("All Files (*)"));
    ui->lineEditBrutalDoom->setText(fileName);
}
