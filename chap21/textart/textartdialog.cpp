#include <QtWidgets>

#include "textartdialog.h"
#include "textartinterface.h"

TextArtDialog::TextArtDialog(const QString &text, QWidget *parent)
    : QDialog(parent)
{
    listWidget = new QListWidget;
    listWidget->setViewMode(QListWidget::IconMode);
    listWidget->setMovement(QListWidget::Static);
    listWidget->setIconSize(QSize(260, 80));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    loadPlugins();
    populateListWidget(text);

    setWindowTitle(tr("Text Art"));
}

QPixmap TextArtDialog::selectedPixmap() const
{
    if (!listWidget->currentItem())
        return QPixmap();

    return listWidget->currentItem()->data(Qt::DecorationRole)
                                     .value<QPixmap>();
}

QDir TextArtDialog::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

void TextArtDialog::loadPlugins()
{
    QDir pluginsDir = directoryOf("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        if (TextArtInterface *interface =
                    qobject_cast<TextArtInterface *>(loader.instance()))
            interfaces.append(interface);
    }
}

void TextArtDialog::populateListWidget(const QString &text)
{
    QSize iconSize = listWidget->iconSize();
    QFont font("Helvetica", iconSize.height(), QFont::Bold);
    QPen pen(QColor("darkseagreen"));

    QLinearGradient gradient(0, 0, iconSize.width() / 2,
                             iconSize.height() / 2);
    gradient.setColorAt(0.0, QColor("darkolivegreen"));
    gradient.setColorAt(0.8, QColor("darkgreen"));
    gradient.setColorAt(1.0, QColor("lightgreen"));

    foreach (TextArtInterface *interface, interfaces) {
        foreach (QString effect, interface->effects()) {
            QListWidgetItem *item = new QListWidgetItem(effect,
                                                        listWidget);
            QPixmap pixmap = interface->applyEffect(effect, text, font,
                                                    iconSize, pen,
                                                    gradient);
            item->setData(Qt::DecorationRole, pixmap);
        }
    }
    listWidget->setCurrentRow(0);
}
