#ifndef DIRECTORYVIEWER_H
#define DIRECTORYVIEWER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QDirModel;
class QTreeView;
QT_END_NAMESPACE

class DirectoryViewer : public QDialog
{
    Q_OBJECT

public:
    DirectoryViewer(QWidget *parent = 0);

private slots:
    void createDirectory();
    void remove();

private:
    QTreeView *treeView;
    QDirModel *model;
    QDialogButtonBox *buttonBox;
};

#endif
