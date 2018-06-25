#include "ipmanager.h"

IPManager::IPManager()
{

}

bool IPManager::addressExists(const QString &address)
{
    for (IPAddress *ip : ipVector){
        if (ip->getAddress() == address) {
            return true;
        }
    }
    return false;
}

void IPManager::addAddress(QString &address)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(address);
    ipVector.push_back(new IPAddress(address, item));
}

bool IPManager::removeAddress(QString &address)
{
    for (size_t i=0; i<ipVector.size(); i++){
        if (ipVector.at(i)->getAddress() == address) {
            delete ipVector.at(i)->getListItem();
            ipVector.erase(ipVector.begin() + i);
            return true;
        }
    }
    return false;
}

QListWidgetItem *IPManager::getQListWidgetItemForAddress(QString address)
{
    for (IPAddress *ip : ipVector){
        if (ip->getAddress() == address) {
            return ip->getListItem();
        }
    }
    return nullptr;
}
