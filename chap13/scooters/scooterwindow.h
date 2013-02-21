#ifndef SCOOTERWINDOW_H
#define SCOOTERWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSqlTableModel;
class QTableView;
QT_END_NAMESPACE

enum {
    Scooter_Id = 0,
    Scooter_Name = 1,
    Scooter_MaxSpeed = 2,
    Scooter_MaxRange = 3,
    Scooter_Weight = 4,
    Scooter_Description = 5
};

class ScooterWindow : public QWidget
{
    Q_OBJECT

public:
    ScooterWindow();

private:
    QSqlTableModel *model;
    QTableView *view;
};

#endif
