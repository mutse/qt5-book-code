#include <QtWidgets>

#include "candydialog.h"

CandyDialog::CandyDialog(QWidget *parent)
    : QDialog(parent)
{
    nameComboBox = new QComboBox;
    nameComboBox->setEditable(true);
    nameComboBox->addItem("Albert Camus");
    nameComboBox->addItem("Dag Solstad");
    nameComboBox->addItem("Haruki Murakami");
    nameComboBox->addItem("Mark Haddon");

    nameLabel = new QLabel(tr("&Name:"));
    nameLabel->setBuddy(nameComboBox);

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setText("password1");

    passwordLabel = new QLabel(tr("&Password:"));
    passwordLabel->setBuddy(passwordLineEdit);

    countryComboBox = new QComboBox;
    countryComboBox->addItem(tr("France"));
    countryComboBox->addItem(tr("Germany"));
    countryComboBox->addItem(tr("United States of America"));
    countryComboBox->addItem(tr("United Kingdom"));
    countryComboBox->addItem(tr("Other"));

    countryLabel = new QLabel(tr("&Country:"));
    countryLabel->setBuddy(countryComboBox);

    professionListWidget = new QListWidget;
    professionListWidget->addItem(tr("Ambassador"));
    professionListWidget->addItem(tr("Cab driver"));
    professionListWidget->addItem(tr("Psychologist"));
    professionListWidget->addItem(tr("Scientist"));
    professionListWidget->addItem(tr("Tax collector"));

    professionLabel = new QLabel(tr("P&rofession:"));
    professionLabel->setBuddy(professionListWidget);

    acceptCheckBox = new QCheckBox(tr("I accept the terms and "
                                      "conditions"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameComboBox, 0, 1);
    mainLayout->addWidget(passwordLabel, 1, 0);
    mainLayout->addWidget(passwordLineEdit, 1, 1);
    mainLayout->addWidget(countryLabel, 2, 0);
    mainLayout->addWidget(countryComboBox, 2, 1);
    mainLayout->addWidget(professionListWidget, 3, 1, 3, 1);
    mainLayout->addWidget(professionLabel, 4, 0);
    mainLayout->addWidget(acceptCheckBox, 6, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 7, 0, 1, 2);
    mainLayout->setRowMinimumHeight(3, 0);
    mainLayout->setRowStretch(5, 1);
    setLayout(mainLayout);

    setWindowTitle(tr("Candy"));
}
