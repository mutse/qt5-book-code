#include <QtWidgets>

#include "bronzedialog.h"

BronzeDialog::BronzeDialog(QWidget *parent)
    : QDialog(parent)
{
    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setAlignment(Qt::AlignCenter);

    dateLabel = new QLabel(tr("&Date:"));
    dateLabel->setBuddy(dateEdit);

    timeEdit = new QTimeEdit(QTime(9, 15, 0));
    timeEdit->setAlignment(Qt::AlignCenter);

    timeLabel = new QLabel(tr("&Time:"));
    timeLabel->setBuddy(timeEdit);

    durationSpinBox = new QSpinBox;
    durationSpinBox->setAlignment(Qt::AlignCenter);
    durationSpinBox->setSuffix(tr(" hr"));
    durationSpinBox->setValue(3);

    durationLabel = new QLabel(tr("D&uration:"));
    durationLabel->setBuddy(durationSpinBox);

    priceSpinBox = new QDoubleSpinBox;
    priceSpinBox->setAlignment(Qt::AlignCenter);
    priceSpinBox->setMaximum(10000.00);
    priceSpinBox->setValue(500.00);

    priceLabel = new QLabel(tr("&Price:"));
    priceLabel->setBuddy(priceSpinBox);

    agendaTreeWidget = new QTreeWidget;
    agendaTreeWidget->setAlternatingRowColors(true);
    agendaTreeWidget->setHorizontalScrollBarPolicy(
            Qt::ScrollBarAlwaysOff);
    agendaTreeWidget->setVerticalScrollBarPolicy(
            Qt::ScrollBarAlwaysOff);
    agendaTreeWidget->setColumnCount(1);
    agendaTreeWidget->header()->hide();
    populateAgendaTreeWidget();

    agendaLabel = new QLabel(tr("&Agenda:"));
    agendaLabel->setBuddy(agendaTreeWidget);
    agendaLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    reminderCheckBox = new QCheckBox(tr("&Send me a reminder"));
    reminderCheckBox->setCheckState(Qt::PartiallyChecked);

    editableCheckBox = new QCheckBox(tr("&Item is editable"));
    editableCheckBox->setChecked(true);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Save
                                     | QDialogButtonBox::Cancel);

    connect(editableCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(editableStateChanged(bool)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(dateLabel, 0, 0);
    mainLayout->addWidget(dateEdit, 0, 1);
    mainLayout->addWidget(timeLabel, 0, 3);
    mainLayout->addWidget(timeEdit, 0, 4);
    mainLayout->addWidget(durationLabel, 1, 0);
    mainLayout->addWidget(durationSpinBox, 1, 1);
    mainLayout->addWidget(priceLabel, 1, 3);
    mainLayout->addWidget(priceSpinBox, 1, 4);
    mainLayout->addWidget(agendaTreeWidget, 2, 1, 2, 4);
    mainLayout->addWidget(agendaLabel, 3, 0);
    mainLayout->addWidget(reminderCheckBox, 4, 0, 1, 2);
    mainLayout->addWidget(editableCheckBox, 4, 3, 1, 2, Qt::AlignRight);
    mainLayout->addWidget(buttonBox, 5, 0, 1, 5);
    mainLayout->setRowStretch(3, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnMinimumWidth(3, 12);
    mainLayout->setColumnStretch(4, 1);
    setLayout(mainLayout);

    setWindowTitle(tr("Bronze"));
}

void BronzeDialog::editableStateChanged(bool editable)
{
    dateLabel->setEnabled(editable);
    timeLabel->setEnabled(editable);
    durationLabel->setEnabled(editable);
    priceLabel->setEnabled(editable);
    agendaLabel->setEnabled(editable);
    dateEdit->setEnabled(editable);
    timeEdit->setEnabled(editable);
    durationSpinBox->setEnabled(editable);
    priceSpinBox->setEnabled(editable);
    reminderCheckBox->setEnabled(editable);
    agendaTreeWidget->setEnabled(editable);
    buttonBox->button(QDialogButtonBox::Save)->setEnabled(editable);
}

void BronzeDialog::populateAgendaTreeWidget()
{
    QTreeWidgetItem *item1 = new QTreeWidgetItem(agendaTreeWidget);
    item1->setText(0, tr("1. Call to order"));

    QTreeWidgetItem *item2 = new QTreeWidgetItem(agendaTreeWidget);
    item2->setText(0, tr("2. Approval of Minutes"));

    QTreeWidgetItem *item3 = new QTreeWidgetItem(agendaTreeWidget);
    item3->setText(0, tr("3. New Business"));
    item3->setExpanded(true);

    QTreeWidgetItem *item31 = new QTreeWidgetItem(item3);
    item31->setText(0, tr("3.1. Introduction of task force members"));

    QTreeWidgetItem *item32 = new QTreeWidgetItem(item3);
    item32->setText(0, tr("3.2. Welcome address"));

    QTreeWidgetItem *item33 = new QTreeWidgetItem(item3);
    item33->setText(0, tr("3.3. Review timeline for task force work"));

    QTreeWidgetItem *item4 = new QTreeWidgetItem(agendaTreeWidget);
    item4->setText(0, tr("4. Arrangements for future meetings"));

    QTreeWidgetItem *item41 = new QTreeWidgetItem(item4);
    item41->setText(0, tr("4.1. Dates"));

    QTreeWidgetItem *item42 = new QTreeWidgetItem(item4);
    item42->setText(0, tr("4.2. Agenda items for next meeting"));

    QTreeWidgetItem *item5 = new QTreeWidgetItem(agendaTreeWidget);
    item5->setText(0, tr("5. Ajournment"));
}
