#ifndef IPMANAGER_H
#define IPMANAGER_H

#include <cstdlib>
#include "ipaddress.h"
#include <QListWidgetItem>

class IPManager
{
public:
    IPManager();

    bool addressExists(const QString &address);
    void addAddress(QString &address);
    bool removeAddress(QString &address);
    QListWidgetItem* getQListWidgetItemForAddress(QString address);
private:
    std::vector<IPAddress*> ipVector;
};

#endif // IPMANAGER_H
