#include <QtWidgets>
#include <QtScript>
#include <iostream>

#include "pumpspreadsheet.h"
#include "scripting.h"

Q_DECLARE_METATYPE(PumpFilter)
Q_DECLARE_METATYPE(PumpFilter *)

bool runScript(const QString &fileName, const QStringList &args)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString script = in.readAll();
    file.close();

    QScriptEngine interpreter;

    PumpSpreadsheet spreadsheet;
    QScriptValue qsSpreadsheet = interpreter.newQObject(&spreadsheet);
    interpreter.globalObject().setProperty("spreadsheet",
                                           qsSpreadsheet);

    QScriptValue qsArgs = qScriptValueFromSequence(&interpreter, args);
    interpreter.globalObject().setProperty("args", qsArgs);

    QScriptValue qsMetaObject =
            interpreter.newQMetaObject(spreadsheet.metaObject());
    interpreter.globalObject().setProperty("PumpSpreadsheet",
                                           qsMetaObject);

    PumpFilterPrototype filterProto;
    QScriptValue qsFilterProto = interpreter.newQObject(&filterProto);
    interpreter.setDefaultPrototype(qMetaTypeId<PumpFilter>(),
                                    qsFilterProto);

    QScriptValue qsFilterCtor =
            interpreter.newFunction(pumpFilterConstructor,
                                    qsFilterProto);
    interpreter.globalObject().setProperty("PumpFilter", qsFilterCtor);

    interpreter.evaluate(script);
    if (interpreter.hasUncaughtException()) {
        std::cerr << "Uncaught exception at line "
                  << interpreter.uncaughtExceptionLineNumber() << ": "
                  << qPrintable(interpreter.uncaughtException()
                                           .toString())
                  << std::endl << "Backtrace: "
                  << qPrintable(interpreter.uncaughtExceptionBacktrace()
                                           .join(", "))
                  << std::endl;
        return false;
    }

    return true;
}

QScriptValue pumpFilterConstructor(QScriptContext * /* context */,
                                   QScriptEngine *interpreter)
{
    return interpreter->toScriptValue(PumpFilter());
}

PumpFilterPrototype::PumpFilterPrototype(QObject *parent)
    : QObject(parent)
{
}

void PumpFilterPrototype::setFromDate(const QDate &date)
{
    wrappedFilter()->fromDate = date;
}

QDate PumpFilterPrototype::fromDate() const
{
    return wrappedFilter()->fromDate;
}

void PumpFilterPrototype::setToDate(const QDate &date)
{
    wrappedFilter()->toDate = date;
}

QDate PumpFilterPrototype::toDate() const
{
    return wrappedFilter()->toDate;
}

void PumpFilterPrototype::setFromTime(const QTime &time)
{
    wrappedFilter()->fromTime = time;
}

QTime PumpFilterPrototype::fromTime() const
{
    return wrappedFilter()->fromTime;
}

void PumpFilterPrototype::setToTime(const QTime &time)
{
    wrappedFilter()->toTime = time;
}

QTime PumpFilterPrototype::toTime() const
{
    return wrappedFilter()->toTime;
}

void PumpFilterPrototype::setPump(const QString &pump)
{
    wrappedFilter()->pump = pump;
}

QString PumpFilterPrototype::pump() const
{
    return wrappedFilter()->pump;
}

void PumpFilterPrototype::setCompany(const QString &company)
{
    wrappedFilter()->company = company;
}

QString PumpFilterPrototype::company() const
{
    return wrappedFilter()->company;
}

void PumpFilterPrototype::setUser(const QString &user)
{
    wrappedFilter()->user = user;
}

QString PumpFilterPrototype::user() const
{
    return wrappedFilter()->user;
}

void PumpFilterPrototype::setFromQuantity(double quantity)
{
    wrappedFilter()->fromQuantity = quantity;
}

double PumpFilterPrototype::fromQuantity() const
{
    return wrappedFilter()->fromQuantity;
}

void PumpFilterPrototype::setToQuantity(double quantity)
{
    wrappedFilter()->toQuantity = quantity;
}

double PumpFilterPrototype::toQuantity() const
{
    return wrappedFilter()->toQuantity;
}

void PumpFilterPrototype::setStatus(const QString &status)
{
    wrappedFilter()->status = status;
}

QString PumpFilterPrototype::status() const
{
    return wrappedFilter()->status;
}

PumpFilter *PumpFilterPrototype::wrappedFilter() const
{
    return qscriptvalue_cast<PumpFilter *>(thisObject());
}
