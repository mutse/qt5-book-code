#ifndef SCRIPTING_H
#define SCRIPTING_H

#include <QDate>
#include <QObject>
#include <QScriptable>
#include <QTime>

QT_BEGIN_NAMESPACE
class QScriptValue;
class PumpFilter;
QT_END_NAMESPACE

bool runScript(const QString &fileName, const QStringList &args);

QScriptValue pumpFilterConstructor(QScriptContext *context,
                                   QScriptEngine *interpreter);

class PumpFilterPrototype : public QObject, public QScriptable
{
    Q_OBJECT
    Q_PROPERTY(QDate fromDate READ fromDate WRITE setFromDate)
    Q_PROPERTY(QDate toDate READ toDate WRITE setToDate)
    Q_PROPERTY(QTime fromTime READ fromTime WRITE setFromTime)
    Q_PROPERTY(QTime toTime READ toTime WRITE setToTime)
    Q_PROPERTY(QString pump READ pump WRITE setPump)
    Q_PROPERTY(QString company READ company WRITE setCompany)
    Q_PROPERTY(QString user READ user WRITE setUser)
    Q_PROPERTY(double fromQuantity READ fromQuantity
               WRITE setFromQuantity)
    Q_PROPERTY(double toQuantity READ toQuantity WRITE setToQuantity)
    Q_PROPERTY(QString status READ status WRITE setStatus)

public:
    PumpFilterPrototype(QObject *parent = 0);

    void setFromDate(const QDate &date);
    QDate fromDate() const;
    void setToDate(const QDate &date);
    QDate toDate() const;

    void setFromTime(const QTime &time);
    QTime fromTime() const;
    void setToTime(const QTime &time);
    QTime toTime() const;

    void setPump(const QString &pump);
    QString pump() const;
    void setCompany(const QString &company);
    QString company() const;
    void setUser(const QString &user);
    QString user() const;

    void setFromQuantity(double quantity);
    double fromQuantity() const;
    void setToQuantity(double quantity);
    double toQuantity() const;

    void setStatus(const QString &status);
    QString status() const;

private:
    PumpFilter *wrappedFilter() const;
};

#endif
