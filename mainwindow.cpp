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

    PWADvbox = nullptr;

    config = new Config();
    if (!config->loadConfig()){
        if (!config->configExists()) {
            showError(tr("Błąd ładowania pliku."), tr("Nie znaleziono pliku konfiguracyjnego."));
            on_actionSettings_triggered();
        } else {
            showError(tr("Błąd ładowania pliku."), tr("Nie udało się odczytać pliku konfiguracyjnego."));
        }
    }

    initWADs();

    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(on_runButton_clicked()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(on_refreshButton_clicked()));

    setIPAdresses();

    this->adjustSize();
}

MainWindow::~MainWindow()
{
    delete config;
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

void MainWindow::getWADs()
{
    QStringList list;
    QDir *currentDir = new QDir(config->getGameLocation());
    list = currentDir->entryList();
    list = list.filter(QRegExp("(.wad|.WAD)"));
    std::ifstream in;
    for (auto i: list){
        in.open(config->getGameLocation().toStdString()+i.toStdString());
        char buffer[4];
        in.read(buffer, 4);
        in.close();
        std::string str="";
        for (auto i: buffer){
            str += i;
        }
        if (str == "IWAD"){
            IWADsVector.push_back(i);
        } else {
            if (str == "PWAD"){
                PWADsVector.push_back(i);
            }
        }
    }
    delete currentDir;
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

void MainWindow::cwDestroyed()
{
    delete cw;
}

void MainWindow::setIPAdresses()
{
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
}

void MainWindow::setPWADs()
{
    if (PWADvbox != nullptr) {
        delete PWADvbox;
    }
    PWADvbox = new QVBoxLayout;
    for (auto i : PWADCheckBoxVector) {
        delete i;
    }
    PWADCheckBoxVector.clear();
    for (auto i : PWADsVector) {
        PWADCheckBoxVector.push_back(new QCheckBox(i));
        PWADvbox->addWidget(PWADCheckBoxVector.back());
    }
    delete ui->PWADgroupBox->layout();
    ui->PWADgroupBox->setLayout(PWADvbox);

}

void MainWindow::setIWADs()
{
    disconnect(ui->IWADListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_IWADListWidget_currentRowChanged(int)));
    ui->IWADListWidget->clear();
    for (auto i : IWADsVector) {
        ui->IWADListWidget->addItem(i);
    }
    connect(ui->IWADListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_IWADListWidget_currentRowChanged(int)));
}

void MainWindow::initWADs()
{
    clearWADs();
    getWADs();
    setIWADs();
    setPWADs();
}

void MainWindow::clearWADs() {
    PWADsVector.clear();
    IWADsVector.clear();
}

void MainWindow::runGame()
{
    QString list;
    list += "-iwad ";
    int i = ui->IWADListWidget->currentRow();
    if (i == -1) {
        run = false;
        showError("Należy wybrać IWAD.");
        return;
    }
    list += config->getGameLocation()+IWADsVector[i];
    if (ui->radioServer->isChecked()){
        setServerOptions(list);
    } else {
        if (!setClientOptions(list)){
            return;
        }
    }
    QString program;
    setCommonOptions(list, program);
    if (run && myProcess->state() == QProcess::NotRunning){
        ui->textEdit->clear();
        ui->textEdit->append("<b>"+program+"<br></b>");
        myProcess->setProcessChannelMode ( QProcess::MergedChannels );
        connect(myProcess, SIGNAL(readyReadStandardError()), this, SLOT(updateError()));
        connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(updateText()));
        connect(myProcess, SIGNAL(finished(int)), this, SLOT(processFinished()));
        myProcess->start(program);
    }
}

void MainWindow::showError(QString title, QString message)
{
    QMessageBox msgBox(QMessageBox::Warning, title, message, QMessageBox::Ok, this);
    msgBox.exec();
}

void MainWindow::showError(QString message)
{
     QMessageBox msgBox(QMessageBox::Warning, "Doom launcher", message, QMessageBox::Ok, this);
    msgBox.exec();
}

void MainWindow::setDOOMOptions()
{
    ui->groupBox_4->setHidden(false);
    ui->labelEp->setText(tr("Epizod:"));
    ui->labelMap->setText(tr("Mapa:"));
    ui->labelEp->setHidden(false);
    ui->labelMap->setHidden(false);
    ui->spinBoxEp->setHidden(false);
    ui->spinBoxMap->setHidden(false);
    ui->spinBoxEp->setMaximum(4);
}

void MainWindow::setDOOM2Options()
{
    ui->groupBox_4->setHidden(false);
    ui->labelEp->setText(tr("Mapa:"));
    ui->labelMap->setText(tr("Mapa:"));
    ui->labelEp->setHidden(false);
    ui->labelMap->setHidden(true);
    ui->spinBoxEp->setHidden(false);
    ui->spinBoxMap->setHidden(true);
    ui->spinBoxEp->setMaximum(32);
}

bool MainWindow::setClientOptions(QString &list)
{
    if (ui->lineEditIP->text().isEmpty()){
        run = false;
        showError("Należy podać adres IP serwera.");
        return false;
    } else {
        list += " -join ";
        list += ui->lineEditIP->text();
        run = true;
    }
    return true;
}

void MainWindow::setServerOptions(QString &list)
{
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
}

void MainWindow::setCommonOptions(QString &list, QString &program)
{
    if (config->getEngineLocation().length() == 0) {
        run = false;
        showError("Nie ustawiono ścieżki do silnika gry.");
        return;
    } else {
        program = config->getEngineLocation()+" -stdout ";
    }

    program += list;

    if (ui->checkBoxBD->isChecked()){
        program += " -file "+config->getBrutalDoomLocation()+" ";
    }
    for (uint i=0; i<PWADsVector.size(); i++) {
        if (PWADCheckBoxVector[i]->checkState() == Qt::Checked){
            if (!program.contains("-file")){
                program += " -file ";
            }
            program += " "+config->getGameLocation()+PWADsVector[i];
        }
    }
    if (ui->lineEditArgs->text() != ""){
        program += " "+ui->lineEditArgs->text();
    }
}

void MainWindow::setOptions()
{
    if (config->getIWADVer() == 1) {
        setDOOMOptions();
    } else {
        setDOOM2Options();
    }
}

void MainWindow::on_actionAutor_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("<h4>Autor: Krzysztof Michalski<br><br>Copyright 2016</h4>"));
    msgBox.setWindowTitle(tr("O autorze"));
    msgBox.exec();
}

void MainWindow::on_actionRun_triggered()
{
    runGame();
}

void MainWindow::on_runButton_clicked()
{
    runGame();
}

void MainWindow::on_killButton_clicked()
{
    myProcess->close();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_refreshButton_clicked()
{
    initWADs();
}

void MainWindow::on_IWADListWidget_currentRowChanged(int currentRow)
{
    if (currentRow > -1){
        if (IWADsVector[currentRow] == "doom.wad" ||
            IWADsVector[currentRow] == "heretic.wad"  ){
                config->setIWADVer(1);
                setOptions();
        } else {
            if (IWADsVector[currentRow] == "doom2.wad" ||
                IWADsVector[currentRow] == "plutonia.wad" ||
                IWADsVector[currentRow] == "tnt.wad" ||
                IWADsVector[currentRow] == "hexen.wad" ||
                IWADsVector[currentRow] == "strife1.wad"  ||
                IWADsVector[currentRow] == "freedoom1.wad"   ||
                IWADsVector[currentRow] == "freedoom2.wad"  ||
                IWADsVector[currentRow] == "freedm.wad" ){
                    config->setIWADVer(2);
                    setOptions();
            } else {
                IWADVerWindow *iwadverwindow = new IWADVerWindow(config, this);
                iwadverwindow->setWindowTitle("Wersja IWAD");
                iwadverwindow->setWindowModality(Qt::NonModal);
                iwadverwindow->exec();
                delete iwadverwindow;
                setOptions();
            }
        }
    }
}

void MainWindow::on_actionSettings_triggered()
{
    cw = new ConfigWindow(config, 0);
    cw->setWindowModality(Qt::NonModal);
    cw->setWindowTitle("Konfiguracja");
    cw->exec();
    delete cw;
    initWADs();
}
