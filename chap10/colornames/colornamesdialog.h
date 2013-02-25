#ifndef COLORNAMESDIALOG_H
#define COLORNAMESDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QLineEdit;
class QListView;
class QSortFilterProxyModel;
class QStringListModel;
QT_END_NAMESPACE

class ColorNamesDialog : public QDialog
{
    Q_OBJECT

public:
    ColorNamesDialog(QWidget *parent = 0);

private slots:
    void reapplyFilter();

private:
    QStringListModel *sourceModel;
    QSortFilterProxyModel *proxyModel;
    QListView *listView;
    QLabel *filterLabel;
    QLabel *syntaxLabel;
    QLineEdit *filterLineEdit;
    QComboBox *syntaxComboBox;
};

#endif
