#ifndef EDITDIALOG_H
#define EDITDILAOG_H

#include <QDialog>

#include "ui_editdialog.h"

QT_BEGIN_NAMESPACE
class QTreeWidget;
class ABItem;
QT_END_NAMESPACE

class EditDialog : public QDialog, private Ui::EditDialog
{
    Q_OBJECT

public:
    EditDialog(QTreeWidget *treeWidget, QWidget *parent = 0);
    EditDialog(ABItem *item, QWidget *parent = 0);

    void accept();

private:
    QTreeWidget *treeWidget;
    ABItem *currentItem;
};

#endif
