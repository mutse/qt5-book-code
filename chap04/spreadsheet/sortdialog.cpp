#include <QtWidgets>

#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryColumnCombo->addItem(tr("None"));

    primaryColumnCombo->setMinimumSize(
            secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while (ch <= last) {
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));
        ch = ch.unicode() + 1;
    }
}
