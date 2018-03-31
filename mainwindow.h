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
#include <QVBoxLayout>
#include <QList>
#include <QListWidgetItem>
#include "config.h"
#include "configwindow.h"
#include "iwadverwindow.h"

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
    void cwDestroyed();

    void on_radioServer_clicked();
    void on_radioClient_clicked();
    void on_actionAutor_triggered();
    void on_actionRun_triggered();
    void on_runButton_clicked();
    void on_killButton_clicked();
    void on_actionExit_triggered();
    void on_refreshButton_clicked();
    void on_IWADListWidget_currentRowChanged(int currentRow);
    void on_actionSettings_triggered();

private:
    std::vector<QString> IWADsVector;
    std::vector<QString> PWADsVector;
    std::vector<QCheckBox*> PWADCheckBoxVector;
    std::vector<QPushButton> PushButtonsVector;

    QVBoxLayout *PWADvbox;

    Config *config;

    void getWADs();
    void setIPAdresses();
    void setPWADs();
    void setIWADs();
    void initWADs();
    void clearWADs();
    void runGame();
    void showError(QString title, QString message);
    void showError(QString message);
    void setDOOMOptions();
    void setDOOM2Options();
    bool setClientOptions(QString &list);
    void setServerOptions(QString &list);
    void setCommonOptions(QString &list, QString &program);
    void setOptions();

    bool run = true;
    bool showConfigWindow = false;
    QProcess *myProcess = new QProcess();
    ConfigWindow *cw = nullptr;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
