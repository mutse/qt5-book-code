#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QSet>

#include "ui_filterdialog.h"

QT_BEGIN_NAMESPACE
class PumpFilter;
class PumpSpreadsheet;
QT_END_NAMESPACE

class FilterDialog : public QDialog, private Ui::FilterDialog
{
    Q_OBJECT

public:
    FilterDialog(QWidget *parent = 0);

    void initFromSpreadsheet(PumpSpreadsheet *spreadsheet);
    PumpFilter filter() const;

private:
    void populateComboBox(QComboBox *comboBox,
                          const QSet<QString> &texts);
    QString comboBoxText(const QComboBox *comboBox) const;
};

#endif
