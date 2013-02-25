#ifndef CANDYDIALOG_H
#define CANDYDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QListWidget;
QT_END_NAMESPACE

class CandyDialog : public QDialog
{
    Q_OBJECT

public:
    CandyDialog(QWidget *parent = 0);

private:
    QLabel *nameLabel;
    QLabel *passwordLabel;
    QLabel *countryLabel;
    QLabel *professionLabel;
    QComboBox *nameComboBox;
    QLineEdit *passwordLineEdit;
    QComboBox *countryComboBox;
    QListWidget *professionListWidget;
    QCheckBox *acceptCheckBox;
    QDialogButtonBox *buttonBox;
};

#endif
