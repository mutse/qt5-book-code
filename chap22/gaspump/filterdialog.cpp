#include <QtWidgets>

#include "filterdialog.h"
#include "pumpspreadsheet.h"

FilterDialog::FilterDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void FilterDialog::initFromSpreadsheet(PumpSpreadsheet *spreadsheet)
{
    QSet<QString> pumps;
    QSet<QString> users;
    QSet<QString> companies;
    QSet<QString> statuses;

    for (int row = 0; row < spreadsheet->rowCount(); ++row) {
        pumps.insert(spreadsheet->item(row, PumpSpreadsheet::Pump)
                                ->text());
        users.insert(spreadsheet->item(row, PumpSpreadsheet::User)
                                ->text());
        companies.insert(spreadsheet->item(row,
                                           PumpSpreadsheet::Company)
                                    ->text());
        statuses.insert(spreadsheet->item(row, PumpSpreadsheet::Status)
                                   ->text());
    }

    populateComboBox(pumpComboBox, pumps);
    populateComboBox(userComboBox, users);
    populateComboBox(companyComboBox, companies);
    populateComboBox(statusComboBox, statuses);
}

PumpFilter FilterDialog::filter() const
{
    PumpFilter filter;
    filter.fromDate = fromDateEdit->date();
    filter.toDate = toDateEdit->date();
    filter.fromTime = fromTimeEdit->time();
    filter.toTime = toTimeEdit->time();
    filter.pump = comboBoxText(pumpComboBox);
    filter.company = comboBoxText(companyComboBox);
    filter.user = comboBoxText(userComboBox);
    filter.fromQuantity = fromQuantitySpinBox->value();
    filter.toQuantity = toQuantitySpinBox->value();
    filter.status = comboBoxText(statusComboBox);
    return filter;
}

QString FilterDialog::comboBoxText(const QComboBox *comboBox) const
{
    if (comboBox->currentIndex() == 0) {
        return "";
    } else {
        return comboBox->currentText();
    }
}

void FilterDialog::populateComboBox(QComboBox *comboBox,
                                    const QSet<QString> &texts)
{
    comboBox->clear();
    comboBox->addItem(tr("Any"));

    QStringList textList = texts.toList();
    textList.sort();

    foreach (QString text, textList)
        comboBox->addItem(text);
}
