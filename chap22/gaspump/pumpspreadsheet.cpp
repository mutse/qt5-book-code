#include <QtWidgets>
#include <QtXml>

#include "pumpspreadsheet.h"

PumpSpreadsheet::PumpSpreadsheet(QWidget *parent)
    : QTableWidget(parent)
{
    clearData();
}

void PumpSpreadsheet::clearData()
{
    setRowCount(0);
    setColumnCount(0);
    setColumnCount(ColumnCount);

    setHorizontalHeaderItem(Date, new QTableWidgetItem(tr("Date")));
    setHorizontalHeaderItem(Time, new QTableWidgetItem(tr("Time")));
    setHorizontalHeaderItem(Pump, new QTableWidgetItem(tr("Pump")));
    setHorizontalHeaderItem(Company,
                            new QTableWidgetItem(tr("Company")));
    setHorizontalHeaderItem(User, new QTableWidgetItem(tr("User")));
    setHorizontalHeaderItem(Quantity,
                            new QTableWidgetItem(tr("Quantity")));
    setHorizontalHeaderItem(Status, new QTableWidgetItem(tr("Status")));
}

bool PumpSpreadsheet::addData(const QString &fileName,
                              FileFormat format)
{
    if (format == Pump2000) {
        return addDataInPump2000Format(fileName);
    } else {
        return addDataInGasPumpXmlFormat(fileName);
    }
}

bool PumpSpreadsheet::saveData(const QString &fileName,
                               FileFormat format)
{
    if (format == Pump2000) {
        return saveDataInPump2000Format(fileName);
    } else {
        return saveDataInGasPumpXmlFormat(fileName);
    }
}

void PumpSpreadsheet::sortByColumn(Column column, Qt::SortOrder order)
{
    sortItems(column, order);
}

void PumpSpreadsheet::applyFilter(const PumpFilter &filter)
{
    int row = 0;
    while (row < rowCount()) {
        if (matches(row, filter)) {
            ++row;
        } else {
            removeRow(row);
        }
    }
}

void PumpSpreadsheet::convertUnits(double factor)
{
    for (int row = 0; row < rowCount(); ++row) {
        double newQuantity = factor * text(row, Quantity).toDouble();
        setText(row, Quantity, QString::number(newQuantity));
    }
}

void PumpSpreadsheet::computeTotals(Column column)
{
    sortByColumn(column);

    int row = 0;
    while (row < rowCount()) {
        if (row > 0 && text(row - 1, column) == text(row, column)) {
            double newQuantity = text(row - 1, Quantity).toDouble()
                                 + text(row, Quantity).toDouble();
            setText(row - 1, Quantity, QString::number(newQuantity));
            removeRow(row);
        } else {
            for (int c = 0; c < ColumnCount; ++c) {
                if (c != column && c != Quantity)
                    setText(row, c, "*");
            }
            ++row;
        }
    }
}

void PumpSpreadsheet::setText(int row, int column, const QString &text)
{
    QTableWidgetItem *item = this->item(row, column);
    if (item)
        item->setText(text);
}

QString PumpSpreadsheet::text(int row, int column) const
{
    QTableWidgetItem *item = this->item(row, column);
    if (item) {
        return item->text();
    } else {
        return "";
    }
}

void PumpSpreadsheet::showWarning(const QString &message)
{
    if (isVisible())
        QMessageBox::warning(this, tr("Gas Pump"), message);
}

bool PumpSpreadsheet::addDataInPump2000Format(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showWarning(tr("Cannot read file %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().simplified();
        QStringList fields = line.split(' ');
        if (fields.count() == 7)
            addItem(fields);
    }

    file.close();
    if (file.error() != QFile::NoError) {
        showWarning(tr("Error when reading from %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    return true;
}

bool PumpSpreadsheet::addDataInGasPumpXmlFormat(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showWarning(tr("Cannot read file %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    QXmlStreamReader reader(&file);

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name() == "gpx") {
                readGpxElement(reader);
            } else {
                reader.raiseError(tr("Not a Gas Pump XML file"));
            }
        } else {
            reader.readNext();
        }
    }

    file.close();
    if (file.error() != QFile::NoError) {
        showWarning(tr("Error when writing to %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    return true;
}

void PumpSpreadsheet::readGpxElement(QXmlStreamReader &reader)
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            if (reader.name() == "transaction") {
                readTransactionElement(reader);
            } else {
                reader.raiseError(tr("Unknown element %1")
                                  .arg(reader.name().toString()));
            }
        } else {
            reader.readNext();
        }
    }
}

bool PumpSpreadsheet::saveDataInPump2000Format(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showWarning(tr("Cannot write file %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);

    for (int row = 0; row < rowCount(); ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            out << text(row, column);
            if (column < ColumnCount - 1) {
                out << "\t";
            } else {
                out << endl;
            }
        }
    }

    file.close();
    if (file.error() != QFile::NoError) {
        showWarning(tr("Error when writing to %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    return true;
}

void PumpSpreadsheet::readTransactionElement(QXmlStreamReader &reader)
{
    QMap<QString, QString> map;

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            QString key = reader.name().toString();
            map.insert(key, reader.readElementText());
        }
        reader.readNext();
    }

    QStringList fields;
    fields << map.value("date") << map.value("time")
           << map.value("pump") << map.value("company")
           << map.value("user") << map.value("quantity")
           << map.value("status");
    addItem(fields);
}

bool PumpSpreadsheet::saveDataInGasPumpXmlFormat(
        const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showWarning(tr("Cannot write file %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("gpx");

    for (int row = 0; row < rowCount(); ++row) {
        writer.writeStartElement("transaction");
        writer.writeTextElement("date", text(row, Date));
        writer.writeTextElement("time", text(row, Time));
        writer.writeTextElement("pump", text(row, Pump));
        writer.writeTextElement("company", text(row, Company));
        writer.writeTextElement("user", text(row, User));
        writer.writeTextElement("quantity", text(row, Quantity));
        writer.writeTextElement("status", text(row, Status));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();

    file.close();
    if (file.error() != QFile::NoError) {
        showWarning(tr("Error when writing to %1:\n%2.")
                    .arg(file.fileName())
                    .arg(file.errorString()));
        return false;
    }

    return true;
}

void PumpSpreadsheet::addItem(const QStringList &fields)
{
    int row = rowCount();
    setRowCount(row + 1);

    QTableWidgetItem *dateItem = new QTableWidgetItem;
    dateItem->setData(Qt::DisplayRole,
                      QDate::fromString(fields[0], Qt::ISODate));
    setItem(row, Date, dateItem);

    QTableWidgetItem *timeItem = new QTableWidgetItem;
    timeItem->setData(Qt::DisplayRole,
                      QTime::fromString(fields[1], Qt::ISODate));
    setItem(row, Time, timeItem);

    QTableWidgetItem *pumpItem = new QTableWidgetItem(fields[2]);
    pumpItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setItem(row, Pump, pumpItem);

    QTableWidgetItem *companyItem = new QTableWidgetItem(fields[3]);
    companyItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setItem(row, Company, companyItem);

    QTableWidgetItem *userItem = new QTableWidgetItem(fields[4]);
    userItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setItem(row, User, userItem);

    QTableWidgetItem *quantityItem = new QTableWidgetItem;
    quantityItem->setData(Qt::DisplayRole, fields[5].toDouble());
    quantityItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setItem(row, Quantity, quantityItem);

    QTableWidgetItem *statusItem = new QTableWidgetItem(fields[6]);
    setItem(row, Status, statusItem);
}

bool PumpSpreadsheet::matches(int row, const PumpFilter &filter) const
{
    QDate date = item(row, Date)->data(Qt::DisplayRole).toDate();
    QTime time = item(row, Time)->data(Qt::DisplayRole).toTime();
    QString pump = text(row, Pump);
    QString company = text(row, Company);
    QString user = text(row, User);
    double quantity = text(row, Quantity).toDouble();
    QString status = text(row, Status);

    return (date >= filter.fromDate && date <= filter.toDate)
           && (time >= filter.fromTime && time <= filter.toTime)
           && (filter.pump.isEmpty() || pump == filter.pump)
           && (filter.company.isEmpty() || company == filter.company)
           && (filter.user.isEmpty() || user == filter.user)
           && (quantity >= filter.fromQuantity
               && quantity <= filter.toQuantity)
           && (filter.status.isEmpty() || status == filter.status);
}

PumpFilter::PumpFilter()
{
    fromDate.setDate(1900, 1, 1);
    toDate.setDate(7999, 12, 31);
    fromTime.setHMS(0, 0, 0);
    toTime.setHMS(23, 59, 59);
    fromQuantity = 0.0;
    toQuantity = 1000000000.0;
}
