#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->groupOptionsServer->setHidden(true);
    ui->radioCoop->setChecked(true);
    ui->radioHard->setChecked(true);
    ui->radioClient->setChecked(true);
    ui->groupBox_3->setHidden(true);
    setWADS();

    connect(ui->actionUrchom, SIGNAL(triggered()), this, SLOT(on_pushButton_clicked()));

    int i = 0;

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)){
            QString ip = address.toString();
            if (ip.toStdString().substr(0,3) != "169"){
                if (i==0){
                    ui->labelIPHost->setText(address.toString());
                    i++;
                }else{
                    ui->labelIPHost->setText(ui->labelIPHost->text()+"<br>"+address.toString());
                }
            }
        }

    }

    this->adjustSize();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioServer_clicked()
{
    ui->groupOptionsServer->setHidden(false);
    ui->groupOptionsClient->setHidden(true);
    ui->groupBox_3->setHidden(false);
    this->adjustSize();
}

void MainWindow::on_radioClient_clicked()
{
    ui->groupOptionsServer->setHidden(true);
    ui->groupOptionsClient->setHidden(false);
    ui->groupBox_3->setHidden(true);
    this->adjustSize();
}

void MainWindow::setWADS()
{
    QStringList list;
    QDir *currentDir = new QDir(".");
    list = currentDir->entryList();
    list = list.filter(QRegExp("(.wad|.WAD)"));
    std::ifstream in;
    for (auto i: list){
        in.open(i.toStdString());
        char buffer[4];
        in.read(buffer, 4);
        in.close();
        std::string str="";
        for (auto i: buffer){
            str += i;
        }
        if (str == "IWAD"){
            ui->listWidget->addItem(i);
            IWADsVector.push_back(i);
        } else {
            if (str == "PWAD"){
                ui->listWidgetPWAD->addItem(i);
                PWADsVector.push_back(i);
            }
        }

    }
    ui->listWidget->setCurrentRow(0);
}

void MainWindow::on_pushButton_clicked()
{
    QString list;
    if(ui->radioServer->isChecked()){
        list += "-iwad ";
        int i = ui->listWidget->currentRow();
        list += IWADsVector[i];
        list += " -host ";
        list += ui->spinBoxPlayers->cleanText();
        if (ui->radioDm->isChecked()){
            list += " -deathmatch";
        }
        if (ui->radioEasy->isChecked()){
            list += " -skill 0";
        }else{
            if (ui->radioMedium->isChecked()){
                list += " -skill 1";
            }else{
                if (ui->radioHard->isChecked()){
                    list += " -skill 2";
                }else{
                    if (ui->radioUltra->isChecked()){
                        list += " -skill 3";
                    }else{
                        if (ui->radioUltraUltra->isChecked()){
                            list += " -skill 4";
                        }
                    }
                }
            }
        }
        list += " -warp ";
        list += ui->spinBoxEp->cleanText();
        list += " ";
        list += ui->spinBoxMap->cleanText();
        run = true;
    } else {
        if (ui->radioClient->isChecked()){
            if (ui->lineEditIP->text().isEmpty()){
                run = false;
                ui->textEdit->append("<h3>Należy podać adres IP serwera.</h3>");
            } else {
                list += "-iwad ";
                int i = ui->listWidget->currentRow();
                list += IWADsVector[i];
                list += " -join ";
                list += ui->lineEditIP->text();
                run = true;
            }
        }
    }
    if (run && myProcess->state() == QProcess::NotRunning){
        ui->textEdit->clear();
        QString program;
        if (ui->radioGZD->isChecked()){
            program = "gzdoom -stdout ";
        } else {
            program = "zdoom -stdout ";
        }

        if (ui->checkBoxBD->isChecked()){
            program += " -file brutal.pk3 ";
        }
        program += list;
        QList<QListWidgetItem*> PWADList = ui->listWidgetPWAD->selectedItems();

        if (ui->listWidgetPWAD->currentRow() != -1){
            program += " -file ";
            for (auto i: PWADList){
                program += i->text()+" ";
            }
        }
        if (ui->lineEditArgs->text() != ""){
            program += " "+ui->lineEditArgs->text();
        }

        ui->textEdit->append("<b>"+program+"<br></b>");
        myProcess->setProcessChannelMode ( QProcess::MergedChannels );
        connect(myProcess, SIGNAL(readyReadStandardError()), this, SLOT(updateError()));
        connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(updateText()));
        connect(myProcess, SIGNAL(finished(int)), this, SLOT(processFinished()));
        myProcess->start(program);
    }
}

void MainWindow::updateError()
{
    QByteArray data = myProcess->readAllStandardError();
    ui->textEdit->append("<span style='color: red;'>'"+QString(data)+"</span>");
}

void MainWindow::updateText()
{
    QByteArray data = myProcess->readAllStandardOutput();
    ui->textEdit->append(QString(data));
}

void MainWindow::processFinished()
{
    ui->textEdit->append(tr("<br>####### Zakończono proces #######<br>"));
}

void MainWindow::on_actionWyjd_triggered()
{
    this->close();
}

void MainWindow::on_actionAutor_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("<h4>Autor: Krzysztof Michalski<br><br>Copyright 2016</h4>"));
    msgBox.setWindowTitle(tr("O autorze"));
    msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    myProcess->close();
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if (IWADsVector[currentRow] == "doom.wad" || IWADsVector[currentRow] == "heretic.wad"  ){
        ui->groupBox_4->setHidden(false);
        ui->labelEp->setText(tr("Epizod:"));
        ui->labelMap->setText(tr("Mapa:"));
        ui->labelEp->setHidden(false);
        ui->labelMap->setHidden(false);
        ui->spinBoxEp->setHidden(false);
        ui->spinBoxMap->setHidden(false);
        ui->spinBoxEp->setMaximum(4);
    } else {
        if (IWADsVector[currentRow] == "doom2.wad" || IWADsVector[currentRow] == "plutonia.wad" || IWADsVector[currentRow] == "tnt.wad" || IWADsVector[currentRow] == "hexen.wad" || IWADsVector[currentRow] == "strife1.wad"  || IWADsVector[currentRow] == "freedoom1.wad"   || IWADsVector[currentRow] == "freedoom2.wad"  || IWADsVector[currentRow] == "freedm.wad" ){
            ui->groupBox_4->setHidden(false);
            ui->labelEp->setText(tr("Mapa:"));
            ui->labelMap->setText(tr("Mapa:"));
            ui->labelEp->setHidden(false);
            ui->labelMap->setHidden(true);
            ui->spinBoxEp->setHidden(false);
            ui->spinBoxMap->setHidden(true);
            ui->spinBoxEp->setMaximum(32);
        } else {
            ui->groupBox_4->setHidden(true);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidgetPWAD->clearSelection();
    ui->listWidgetPWAD->setCurrentRow(-1);
}
