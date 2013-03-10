#ifndef HTTPGET_H
#define HTTPGET_H

#include <QFile>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QNetworkReply;
QT_END_NAMESPACE

class HttpGet : public QObject
{
    Q_OBJECT

public:
    HttpGet(QObject *parent = 0);

    void startRequest(const QUrl &url);
    bool getFile(const QUrl &url);

private slots:
    void httpFinished();
    void httpReadyRead();

private:
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile file;
};

#endif
