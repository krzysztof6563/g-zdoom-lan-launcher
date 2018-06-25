#include "ipaddress.h"

IPAddress::IPAddress(QString &address, QListWidgetItem *item)
    : _address(address), _listItem(item)
{

}

QListWidgetItem *IPAddress::getListItem()
{
    return _listItem;
}

void IPAddress::setListItem(QListWidgetItem *listItem)
{
    _listItem = listItem;
}

QString IPAddress::getAddress()
{
    return _address;
}

void IPAddress::setAddress(QString &address)
{
    _address = address;
}
