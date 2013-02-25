#include <QtWidgets>

#include "abitem.h"

ABItem::ABItem(QTreeWidget *treeWidget)
    : QTreeWidgetItem(treeWidget)
{
}

void ABItem::setContact(const QString &contact)
{
    setText(0, contact);
}

void ABItem::setAddress(const QString &address)
{
    QString str = address;
    str.replace("\r\n", ", ");
    setText(1, str);
}

void ABItem::setPhoneNumber(const QString &number)
{
    setText(2, number);
}

void ABItem::remove()
{
    delete this;
}
