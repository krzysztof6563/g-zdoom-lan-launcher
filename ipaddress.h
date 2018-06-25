#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>
#include <QListWidgetItem>

class IPAddress
{
public:
    IPAddress(QString &address, QListWidgetItem *item);


    QListWidgetItem *getListItem();
    void setListItem(QListWidgetItem *listItem);

    QString getAddress();
    void setAddress(QString &address);

private:
    QString _address = "";
    QListWidgetItem *_listItem = nullptr;
};

#endif // IPADDRESS_H
