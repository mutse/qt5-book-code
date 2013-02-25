#include <QtWidgets>

#include "abitem.h"
#include "addressbook.h"
#include "editdialog.h"

AddressBook::AddressBook(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList labels;
    labels << tr("Name") << tr("Address") << tr("Phone Number");

    treeWidget = new QTreeWidget;
    treeWidget->setColumnCount(3);
    treeWidget->setHeaderLabels(labels);
    setCentralWidget(treeWidget);

    createActions();
    createMenus();

    QFile file(QDir::homePath() + "/addressbook.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");

        while (!in.atEnd()) {
            ABItem *entry = new ABItem(treeWidget);
            entry->setContact(in.readLine());
            entry->setAddress(in.readLine());
            entry->setPhoneNumber(in.readLine());
            in.readLine();
        }
    }
}

AddressBook::~AddressBook()
{
    QFile file(QDir::homePath() + "/addressbook.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream output(&file);
        output.setCodec("UTF-8");

        for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
            ABItem *entry =
                    static_cast<ABItem *>(treeWidget->topLevelItem(i));
            output << entry->contact() << endl;
            output << entry->address() << endl;
            output << entry->phoneNumber() << endl;
            output << endl;
        }
    }
}

void AddressBook::createActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    addEntryAction = new QAction(tr("&Add Entry..."), this);
    addEntryAction->setShortcut(tr("Ins"));
    addEntryAction->setStatusTip(tr("Add a new entry to the address "
                                    "book"));
    connect(addEntryAction, SIGNAL(triggered()),
            this, SLOT(addEntry()));

    editEntryAction = new QAction(tr("&Edit Entry..."), this);
    editEntryAction->setShortcut(tr("F2"));
    editEntryAction->setStatusTip(tr("Edit the current address book "
                                     "entry"));
    connect(editEntryAction, SIGNAL(triggered()),
            this, SLOT(editEntry()));

    deleteEntryAction = new QAction(tr("&Delete Entry"), this);
    deleteEntryAction->setShortcut(QKeySequence::Delete);
    deleteEntryAction->setStatusTip(tr("Delete the current address "
                                       "book entry"));
    connect(deleteEntryAction, SIGNAL(triggered()),
            this, SLOT(deleteEntry()));
}

void AddressBook::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addEntryAction);
    editMenu->addAction(editEntryAction);
    editMenu->addAction(deleteEntryAction);
}

ABItem *AddressBook::createEntry(const QString &contact)
{
    ABItem *item = new ABItem(treeWidget);
    item->setContact(contact);
    return item;
}

ABItem *AddressBook::findEntry(const QString &contact) const
{
    QList<QTreeWidgetItem *> items =
            treeWidget->findItems(contact, Qt::MatchExactly, 0);
    if (items.isEmpty())
        return 0;
    return static_cast<ABItem *>(items.first());
}

ABItem *AddressBook::entryAt(int index) const
{
    if (index > treeWidget->topLevelItemCount())
        return 0;
    return static_cast<ABItem *>(treeWidget->topLevelItem(index));
}

int AddressBook::count() const
{
    return treeWidget->topLevelItemCount();
}

void AddressBook::addEntry()
{
    EditDialog dialog(treeWidget, this);
    dialog.exec();
}

void AddressBook::editEntry()
{
    ABItem *item = static_cast<ABItem *>(treeWidget->currentItem());
    if (item) {
        EditDialog dialog(item, this);
        dialog.exec();
    }
}

void AddressBook::deleteEntry()
{
    delete treeWidget->currentItem();
}
