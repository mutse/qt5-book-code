#include <QtWidgets>

#include "trackdelegate.h"
#include "trackeditor.h"

Track::Track(const QString &title, int duration)
{
    this->title = title;
    this->duration = duration;
}

TrackEditor::TrackEditor(QList<Track> *tracks, QWidget *parent)
    : QDialog(parent)
{
    this->tracks = tracks;

    tableWidget = new QTableWidget(tracks->count(), 2);
    tableWidget->setItemDelegate(new TrackDelegate(1));
    tableWidget->setHorizontalHeaderLabels(
            QStringList() << tr("Track") << tr("Duration"));

    for (int row = 0; row < tracks->count(); ++row) {
        Track track = tracks->at(row);

        QTableWidgetItem *item0 = new QTableWidgetItem(track.title);
        tableWidget->setItem(row, 0, item0);

        QTableWidgetItem *item1
             = new QTableWidgetItem(QString::number(track.duration));
        item1->setTextAlignment(Qt::AlignRight);
        tableWidget->setItem(row, 1, item1);
    }

    tableWidget->resizeColumnToContents(0);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    QPushButton *addTrackButton = buttonBox->addButton(tr("&Add Track"),
            QDialogButtonBox::ActionRole);

    connect(addTrackButton, SIGNAL(clicked()), this, SLOT(addTrack()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Track Editor"));
}

void TrackEditor::done(int result)
{
    if (result == QDialog::Accepted) {
        tracks->clear();
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            QString title = tableWidget->item(row, 0)->text();
            QTableWidgetItem *item = tableWidget->item(row, 1);
            int duration = item ? item->text().toInt() : 0;
            tracks->append(Track(title, duration));
        }
    }
    QDialog::done(result);
}

void TrackEditor::addTrack()
{
    tableWidget->insertRow(tableWidget->rowCount());
}
