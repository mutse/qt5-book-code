#ifndef PUMPWINDOW_H
#define PUMPWINDOW_H

#include <QMainWindow>

#include "pumpspreadsheet.h"

class PumpWindow : public QMainWindow
{
    Q_OBJECT

public:
    PumpWindow();

private slots:
    void loadData();
    void appendData();
    void saveData();
    void sortByDateTime();
    void sortByPump();
    void sortByCompany();
    void sortByUser();
    void sortByQuantity();
    void sortByStatus();
    void filter();
    void convertToGallons();
    void convertToLiters();
    void computeTotalsPerDate();
    void computeTotalsPerPump();
    void computeTotalsPerCompany();
    void computeTotalsPerUser();
    void about();

private:
    static PumpSpreadsheet::FileFormat fileFormat(
            const QString &fileName);
    void createActions();
    void createMenus();

    PumpSpreadsheet *spreadsheet;
    QString fileFilters;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *sortSubMenu;
    QMenu *convertSubMenu;
    QMenu *computeTotalsSubMenu;
    QMenu *helpMenu;
    QAction *clearDataAction;
    QAction *loadDataAction;
    QAction *appendDataAction;
    QAction *saveDataAction;
    QAction *exitAction;
    QAction *sortByDateTimeAction;
    QAction *sortByPumpAction;
    QAction *sortByCompanyAction;
    QAction *sortByUserAction;
    QAction *sortByQuantityAction;
    QAction *sortByStatusAction;
    QAction *filterAction;
    QAction *convertToGallonsAction;
    QAction *convertToLitersAction;
    QAction *computeTotalsPerDateAction;
    QAction *computeTotalsPerPumpAction;
    QAction *computeTotalsPerCompanyAction;
    QAction *computeTotalsPerUserAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};

#endif
