#include <QtWidgets>

#include "abitem.h"
#include "editdialog.h"

EditDialog::EditDialog(QTreeWidget *treeWidget, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    this->treeWidget = treeWidget;
    currentItem = 0;

    setWindowTitle(tr("Add Entry"));
}

EditDialog::EditDialog(ABItem *item, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    contactLineEdit->setText(item->contact());
    addressLineEdit->setText(item->address());
    phoneLineEdit->setText(item->phoneNumber());
    treeWidget = item->treeWidget();
    currentItem = item;

    setWindowTitle(tr("Edit Entry"));
}

void EditDialog::accept()
{
    if (!currentItem)
        currentItem = new ABItem(treeWidget);
    currentItem->setContact(contactLineEdit->text());
    currentItem->setAddress(addressLineEdit->text());
    currentItem->setPhoneNumber(phoneLineEdit->text());

    QDialog::accept();
}
