#ifndef PUMPSPREADSHEET_H
#define PUMPSPREADSHEET_H

#include <QDate>
#include <QTableWidget>
#include <QTime>

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
class PumpFilter;
QT_END_NAMESPACE

class PumpSpreadsheet : public QTableWidget
{
    Q_OBJECT
    Q_ENUMS(FileFormat Column)

public:
    enum FileFormat { Pump2000, GasPumpXml };
    enum Column { Date, Time, Pump, Company, User, Quantity, Status,
                  ColumnCount };

    PumpSpreadsheet(QWidget *parent = 0);

public slots:
    void clearData();
    bool addData(const QString &fileName, FileFormat format);
    bool saveData(const QString &fileName, FileFormat format);
    void sortByColumn(Column column,
                      Qt::SortOrder order = Qt::AscendingOrder);
    void applyFilter(const PumpFilter &filter);
    void convertUnits(double factor);
    void computeTotals(Column column);
    void setText(int row, int column, const QString &text);
    QString text(int row, int column) const;

private:
    void showWarning(const QString &message);
    bool addDataInPump2000Format(const QString &fileName);
    bool saveDataInPump2000Format(const QString &fileName);
    bool addDataInGasPumpXmlFormat(const QString &fileName);
    bool saveDataInGasPumpXmlFormat(const QString &fileName);
    void readGpxElement(QXmlStreamReader &reader);
    void readTransactionElement(QXmlStreamReader &reader);
    void addItem(const QStringList &fields);
    bool matches(int row, const PumpFilter &filter) const;
};

class PumpFilter
{
public:
    PumpFilter();

    QDate fromDate;
    QDate toDate;
    QTime fromTime;
    QTime toTime;
    QString pump;
    QString company;
    QString user;
    double fromQuantity;
    double toQuantity;
    QString status;
};

#endif
