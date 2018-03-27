#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QFile>
#include <QTextStream>


class Config
{
public:
    Config();
    ~Config();

    bool loadConfig();
    bool saveConfig();
    bool configExists();

    QString getGameLocation() const;
    void setGameLocation(const QString &value);

    QString getEngineLocation() const;
    void setEngineLocation(const QString &value);

    QString getBrutalDoomLocation() const;
    void setBrutalDoomLocation(const QString &value);

private:
    QString engineLocation;
    QString gameLocation;
    QString brutalDoomLocation;
    QString configName = "launcherConfig.dat";
    QFile *configFile;
};

#endif // CONFIG_H
