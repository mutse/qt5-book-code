#include <QtWidgets>

#include "directoryviewer.h"

DirectoryViewer::DirectoryViewer(QWidget *parent)
    : QDialog(parent)
{
    model = new QDirModel;
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    treeView = new QTreeView;
    treeView->setModel(model);
    treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    treeView->header()->setSortIndicatorShown(true);
    treeView->header()->setSectionsClickable(true); //setClickable(true);

    QModelIndex index = model->index(QDir::currentPath());
    treeView->expand(index);
    treeView->scrollTo(index);
    treeView->resizeColumnToContents(0);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *mkdirButton = buttonBox->addButton(
            tr("&Create Directory..."), QDialogButtonBox::ActionRole);
    QPushButton *removeButton = buttonBox->addButton(tr("&Remove"),
            QDialogButtonBox::ActionRole);
    buttonBox->addButton(tr("&Quit"), QDialogButtonBox::AcceptRole);

    connect(mkdirButton, SIGNAL(clicked()),
            this, SLOT(createDirectory()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeView);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Directory Viewer"));
}

void DirectoryViewer::createDirectory()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;

    QString dirName = QInputDialog::getText(this,
                              tr("Create Directory"),
                              tr("Directory name"));
    if (!dirName.isEmpty()) {
        if (!model->mkdir(index, dirName).isValid())
            QMessageBox::information(this, tr("Create Directory"),
                    tr("Failed to create the directory"));
    }
}

void DirectoryViewer::remove()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;

    bool ok;
    if (model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if (!ok)
        QMessageBox::information(this, tr("Remove"),
                tr("Failed to remove %1").arg(model->fileName(index)));
}
