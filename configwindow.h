#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QFileDialog>
#include "config.h"

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(Config *c, QWidget *parent = 0);
    ~ConfigWindow();

private slots:
    void on_pushButtonGameEngine_clicked();

    void on_pushButtonGameDir_clicked();

    void on_buttonOk_clicked(QAbstractButton *button);

    void on_pushButtonBrutalDoom_clicked();

private:
    Ui::ConfigWindow *ui;

    Config *config;
};

#endif // CONFIGWINDOW_H
