#ifndef FLOWCHARTSYMBOLPICKER_H
#define FLOWCHARTSYMBOLPICKER_H

#include <QDialog>
#include <QMap>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QIcon;
class QListWidget;
QT_END_NAMESPACE

class FlowChartSymbolPicker : public QDialog
{
    Q_OBJECT

public:
    FlowChartSymbolPicker(const QMap<int, QString> &symbolMap,
                          QWidget *parent = 0);

    int selectedId() const { return id; }
    void done(int result);

private:
    QIcon iconForSymbol(const QString &symbolName);

    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;
    int id;
};

#endif
