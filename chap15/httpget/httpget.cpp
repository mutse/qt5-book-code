#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <QUrl>
#include "httpget.h"

HttpGet::HttpGet(QObject *parent)
    : QObject(parent)
{

}

void HttpGet::startRequest(const QUrl &url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
}

bool HttpGet::getFile(const QUrl &url)
{
    if (!url.isValid()) {
        std::cerr << "Error: Invalid URL" << std::endl;
        return false;
    }

    if (url.scheme() != "http") {
        std::cerr << "Error: URL must start with 'http:'" << std::endl;
        return false;
    }

    if (url.path().isEmpty()) {
        std::cerr << "Error: URL has no path" << std::endl;
        return false;
    }

    QString localFileName = QFileInfo(url.path()).fileName();
    if (localFileName.isEmpty())
        localFileName = "httpget.html";

    file.setFileName(localFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(file.fileName()) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    startRequest(url);

    return true;
}

void HttpGet::httpFinished()
{
    file.flush();
    file.close();

    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file.remove();
        std::cerr << "Download failed: " << std::endl;
    }

    reply->deleteLater();
    reply = 0;
    qApp->quit();
}

void HttpGet::httpReadyRead()
{
    file.write(reply->readAll());
}
