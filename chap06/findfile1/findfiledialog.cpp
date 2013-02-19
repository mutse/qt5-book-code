#include <QtWidgets>

#include "findfiledialog.h"

FindFileDialog::FindFileDialog(QWidget *parent)
    : QDialog(parent)
{
    namedLabel = new QLabel(tr("&Named:"), this);
    namedLineEdit = new QLineEdit(this);
    namedLabel->setBuddy(namedLineEdit);

    lookInLabel = new QLabel(tr("&Look in:"), this);
    lookInLineEdit = new QLineEdit(this);
    lookInLabel->setBuddy(lookInLineEdit);

    subfoldersCheckBox = new QCheckBox(tr("Include subfolders"), this);

    QStringList labels;
    labels << tr("Name") << tr("In Folder") << tr("Size")
           << tr("Modified");

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels(labels);

    messageLabel = new QLabel(tr("0 files found"), this);
    messageLabel->setFrameShape(QLabel::Panel);
    messageLabel->setFrameShadow(QLabel::Sunken);

    findButton = new QPushButton(tr("&Find"), this);
    stopButton = new QPushButton(tr("Stop"), this);
    closeButton = new QPushButton(tr("Close"), this);
    helpButton = new QPushButton(tr("Help"), this);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    namedLabel->setGeometry(9, 9, 50, 25);
    namedLineEdit->setGeometry(65, 9, 200, 25);
    lookInLabel->setGeometry(9, 40, 50, 25);
    lookInLineEdit->setGeometry(65, 40, 200, 25);
    subfoldersCheckBox->setGeometry(9, 71, 256, 23);
    tableWidget->setGeometry(9, 100, 256, 100);
    messageLabel->setGeometry(9, 206, 256, 25);
    findButton->setGeometry(271, 9, 85, 32);
    stopButton->setGeometry(271, 47, 85, 32);
    closeButton->setGeometry(271, 84, 85, 32);
    helpButton->setGeometry(271, 199, 85, 32);

    setWindowTitle(tr("Find Files or Folders"));
    setFixedSize(365, 240);
}
