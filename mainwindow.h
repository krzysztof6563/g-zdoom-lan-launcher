#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QHostAddress>
#include <QNetworkInterface>
#include <vector>
#include <fstream>
#include <QCoreApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateError();
    void updateText();
    void processFinished();

    void on_radioServer_clicked();

    void on_radioClient_clicked();

    void on_pushButton_clicked();

    void on_actionWyjd_triggered();

    void on_actionAutor_triggered();

    void on_pushButton_2_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_3_clicked();

private:
    std::vector<QString> IWADsVector;
    std::vector<QString> PWADsVector;
    void setWADS();
    bool run=true;
    QProcess *myProcess = new QProcess();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
