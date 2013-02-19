#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void findClicked();
    void enableFindButton(const QString &text);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif
