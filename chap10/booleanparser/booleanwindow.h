#ifndef BOOLEANWINDOW_H
#define BOOLEANWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTreeView;
class BooleanModel;
QT_END_NAMESPACE

class BooleanWindow : public QWidget
{
    Q_OBJECT

public:
    BooleanWindow();

private slots:
    void booleanExpressionChanged(const QString &expr);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    BooleanModel *booleanModel;
    QTreeView *treeView;
};

#endif
