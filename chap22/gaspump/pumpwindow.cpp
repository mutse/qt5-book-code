#include <QtWidgets>

#include "filterdialog.h"
#include "pumpwindow.h"

const double LitersPerGallon = 3.785411784;
const double GallonsPerLiter = 1.0 / LitersPerGallon;

PumpWindow::PumpWindow()
{
    spreadsheet = new PumpSpreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();

    statusBar()->showMessage(tr("Ready"), 2000);

    fileFilters = tr("Pump 2000 files (*.p20)\n"
                     "Gas Pump XML files (*.gpx)");

    setWindowTitle(tr("Gas Pump"));
}

void PumpWindow::loadData()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open Data File"), ".",
                               fileFilters);
    if (!fileName.isEmpty()) {
        spreadsheet->clearData();
        spreadsheet->addData(fileName, fileFormat(fileName));
    }
}

void PumpWindow::appendData()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open Data File"), ".",
                               fileFilters);
    if (!fileName.isEmpty())
        spreadsheet->addData(fileName, fileFormat(fileName));
}

void PumpWindow::saveData()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Export Data"), ".",
                               fileFilters);
    if (!fileName.isEmpty())
        spreadsheet->saveData(fileName, fileFormat(fileName));
}

void PumpWindow::sortByDateTime()
{
    spreadsheet->sortByColumn(PumpSpreadsheet::Time);
    spreadsheet->sortByColumn(PumpSpreadsheet::Date);
}

void PumpWindow::sortByPump()
{
    spreadsheet->sortByColumn(PumpSpreadsheet::Pump);
}

void PumpWindow::sortByCompany()
{
    spreadsheet->sortByColumn(PumpSpreadsheet::Company);
}

void PumpWindow::sortByUser()
{
    spreadsheet->sortByColumn(PumpSpreadsheet::User);
}

void PumpWindow::sortByQuantity()
{
    spreadsheet->sortByColumn(PumpSpreadsheet::Quantity);
}

void PumpWindow::sortByStatus()
{
    spreadsheet->sortByColumn(PumpSpreadsheet::Status);
}

void PumpWindow::filter()
{
    FilterDialog dialog(this);
    dialog.initFromSpreadsheet(spreadsheet);
    if (dialog.exec())
        spreadsheet->applyFilter(dialog.filter());
}

void PumpWindow::convertToGallons()
{
    spreadsheet->convertUnits(GallonsPerLiter);
}

void PumpWindow::convertToLiters()
{
    spreadsheet->convertUnits(LitersPerGallon);
}

void PumpWindow::computeTotalsPerDate()
{
    spreadsheet->computeTotals(PumpSpreadsheet::Date);
}

void PumpWindow::computeTotalsPerPump()
{
    spreadsheet->computeTotals(PumpSpreadsheet::Pump);
}

void PumpWindow::computeTotalsPerCompany()
{
    spreadsheet->computeTotals(PumpSpreadsheet::Company);
}

void PumpWindow::computeTotalsPerUser()
{
    spreadsheet->computeTotals(PumpSpreadsheet::User);
}

void PumpWindow::about()
{
    QMessageBox::about(this, tr("About Gas Pump"),
            tr("<h2>Gas Pump 1.1</h2>"
               "<p>Copyright &copy; 2008 Software Inc."
               "<p>Gas Pump is a small application that can be "
               "automated using the <i>QtScript</i> module. To run a "
               "script, run the application as follows:"
               "<blockquote><tt>gaspump -script <i>myscript.js</i> "
               "[<i>arguments</i>]</tt></blockquote>"
               "<p>A few scripts are provided in the <tt>scripts</tt> "
               "subdirectory."));
}

PumpSpreadsheet::FileFormat
PumpWindow::fileFormat(const QString &fileName)
{
    if (fileName.endsWith(".p20", Qt::CaseInsensitive)) {
        return PumpSpreadsheet::Pump2000;
    } else {
        return PumpSpreadsheet::GasPumpXml;
    }
}

void PumpWindow::createActions()
{
    clearDataAction = new QAction(tr("&Clear Data"), this);
    clearDataAction->setStatusTip(tr("Clears the entire spreadsheet"));
    connect(clearDataAction, SIGNAL(triggered()),
            spreadsheet, SLOT(clearData()));

    loadDataAction = new QAction(tr("&Load Data..."), this);
    loadDataAction->setStatusTip(tr("Loads the contents of an existing "
                                    "pump data file"));
    connect(loadDataAction, SIGNAL(triggered()),
            this, SLOT(loadData()));

    appendDataAction = new QAction(tr("&Append Data..."), this);
    appendDataAction->setStatusTip(tr("Append the contents of an "
                                      "existing pump data file"));
    connect(appendDataAction, SIGNAL(triggered()),
            this, SLOT(appendData()));

    saveDataAction = new QAction(tr("&Save Data..."), this);
    saveDataAction->setStatusTip(tr("Save the spreadsheet to disk"));
    saveDataAction->setShortcut(tr("Ctrl+S"));
    connect(saveDataAction, SIGNAL(triggered()),
            this, SLOT(saveData()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    sortByDateTimeAction = new QAction(tr("by &Date/Time"), this);
    sortByDateTimeAction->setStatusTip(tr("Sort the transactions "
                                          "chronologically"));
    connect(sortByDateTimeAction, SIGNAL(triggered()),
            this, SLOT(sortByDateTime()));

    sortByPumpAction = new QAction(tr("by &Pump"), this);
    sortByPumpAction->setStatusTip(tr("Sort the transactions by pump"));
    connect(sortByPumpAction, SIGNAL(triggered()),
            this, SLOT(sortByPump()));

    sortByCompanyAction = new QAction(tr("by &Company"), this);
    sortByCompanyAction->setStatusTip(tr("Sort the transactions by "
                                         "company"));
    connect(sortByCompanyAction, SIGNAL(triggered()),
            this, SLOT(sortByCompany()));

    sortByUserAction = new QAction(tr("by &User"), this);
    sortByUserAction->setStatusTip(tr("Sort the transactions by user"));
    connect(sortByUserAction, SIGNAL(triggered()),
            this, SLOT(sortByUser()));

    sortByQuantityAction = new QAction(tr("by &Quantity"), this);
    sortByQuantityAction->setStatusTip(tr("Sort the transactions by "
                                          "quantity"));
    connect(sortByQuantityAction, SIGNAL(triggered()),
            this, SLOT(sortByQuantity()));

    sortByStatusAction = new QAction(tr("by &Status"), this);
    sortByStatusAction->setStatusTip(tr("Sort the transactions by "
                                        "status"));
    connect(sortByStatusAction, SIGNAL(triggered()),
            this, SLOT(sortByStatus()));

    filterAction = new QAction(tr("&Filter..."), this);
    filterAction->setShortcut(tr("Ctrl+F"));
    filterAction->setStatusTip(tr("Filter out transactions based on "
                                  "specific criteria"));
    connect(filterAction, SIGNAL(triggered()), this, SLOT(filter()));

    convertToGallonsAction = new QAction(tr("Liters to &Gallons"),
                                         this);
    convertToGallonsAction->setStatusTip(
            tr("Convert the quantities from liters to U.S. gallons"));
    connect(convertToGallonsAction, SIGNAL(triggered()),
            this, SLOT(convertToGallons()));

    convertToLitersAction = new QAction(tr("Gallons to &Liters"), this);
    convertToGallonsAction->setStatusTip(
            tr("Convert the quantities from U.S. gallons to liters"));
    connect(convertToLitersAction, SIGNAL(triggered()),
            this, SLOT(convertToLiters()));

    computeTotalsPerDateAction = new QAction(tr("per &Date"), this);
    computeTotalsPerDateAction->setStatusTip(
            tr("Compute quantity totals for each date"));
    connect(computeTotalsPerDateAction, SIGNAL(triggered()),
            this, SLOT(computeTotalsPerDate()));

    computeTotalsPerPumpAction = new QAction(tr("per &Pump"), this);
    computeTotalsPerPumpAction->setStatusTip(
            tr("Compute quantity totals for each pump"));
    connect(computeTotalsPerPumpAction, SIGNAL(triggered()),
            this, SLOT(computeTotalsPerPump()));

    computeTotalsPerCompanyAction = new QAction(tr("per &Company"),
                                                this);
    computeTotalsPerCompanyAction->setStatusTip(
            tr("Compute quantity totals for each company"));
    connect(computeTotalsPerCompanyAction, SIGNAL(triggered()),
            this, SLOT(computeTotalsPerCompany()));

    computeTotalsPerUserAction = new QAction(tr("per &User"), this);
    computeTotalsPerUserAction->setStatusTip(
            tr("Compute quantity totals for each user"));
    connect(computeTotalsPerUserAction, SIGNAL(triggered()),
            this, SLOT(computeTotalsPerUser()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void PumpWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(clearDataAction);
    fileMenu->addAction(loadDataAction);
    fileMenu->addAction(appendDataAction);
    fileMenu->addAction(saveDataAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));

    sortSubMenu = editMenu->addMenu(tr("&Sort"));
    sortSubMenu->addAction(sortByDateTimeAction);
    sortSubMenu->addAction(sortByPumpAction);
    sortSubMenu->addAction(sortByCompanyAction);
    sortSubMenu->addAction(sortByUserAction);
    sortSubMenu->addAction(sortByQuantityAction);
    sortSubMenu->addAction(sortByStatusAction);

    editMenu->addAction(filterAction);

    convertSubMenu = editMenu->addMenu(tr("&Convert"));
    convertSubMenu->addAction(convertToGallonsAction);
    convertSubMenu->addAction(convertToLitersAction);

    computeTotalsSubMenu = editMenu->addMenu(tr("Compute &Totals"));
    computeTotalsSubMenu->addAction(computeTotalsPerDateAction);
    computeTotalsSubMenu->addAction(computeTotalsPerPumpAction);
    computeTotalsSubMenu->addAction(computeTotalsPerCompanyAction);
    computeTotalsSubMenu->addAction(computeTotalsPerUserAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}
