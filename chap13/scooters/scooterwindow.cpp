#include <QtWidgets>
#include <QtSql>

#include "scooterwindow.h"

ScooterWindow::ScooterWindow()
{
    model = new QSqlTableModel(this);
    model->setTable("scooter");
    model->setSort(Scooter_Name, Qt::AscendingOrder);
    model->setHeaderData(Scooter_Name, Qt::Horizontal, tr("Name"));
    model->setHeaderData(Scooter_MaxSpeed, Qt::Horizontal, tr("MPH"));
    model->setHeaderData(Scooter_MaxRange, Qt::Horizontal, tr("Miles"));
    model->setHeaderData(Scooter_Weight, Qt::Horizontal, tr("Lbs"));
    model->setHeaderData(Scooter_Description, Qt::Horizontal,
                         tr("Description"));
    model->select();

    view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setColumnHidden(Scooter_Id, true);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header = view->horizontalHeader();
    header->setStretchLastSection(true);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    setLayout(mainLayout);

    setWindowTitle(tr("Scooters"));
}
