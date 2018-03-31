#include "config.h"

Config::Config()
{
    configFile = new QFile(configName);
}

Config::~Config()
{
    delete configFile;
}

bool Config::loadConfig()
{
    if (configExists()){
        if (!configFile->open(QIODevice::ReadOnly | QIODevice::Text)){
            return false;
        }
        QTextStream in(configFile);
        setGameLocation(in.readLine());
        setEngineLocation(in.readLine());
        setBrutalDoomLocation(in.readLine());
    } else {
        configFile->close();
        return false;
    }
    configFile->close();
    return true;
}

bool Config::saveConfig()
{
    if (!configFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        return false;
    }
    QTextStream out(configFile);
    out << gameLocation << "\n";
    out << engineLocation << "\n";
    out << brutalDoomLocation;
    configFile->close();
    return true;
}

bool Config::configExists()
{
    return configFile->exists();

}

QString Config::getGameLocation() const
{
    return gameLocation;
}

void Config::setGameLocation(const QString &value)
{
    gameLocation = value;
}

QString Config::getEngineLocation() const
{
    return engineLocation;
}

void Config::setEngineLocation(const QString &value)
{
    engineLocation = value;
}

QString Config::getBrutalDoomLocation() const
{
    return brutalDoomLocation;
}

void Config::setBrutalDoomLocation(const QString &value)
{
    brutalDoomLocation = value;
}

int Config::getIWADVer() const
{
    return IWADVer;
}

void Config::setIWADVer(int value)
{
    IWADVer = value;
}
