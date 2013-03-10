#include <QtCore>
#include <QtNetwork>
#include <iostream>

#include "spider.h"

Spider::Spider(QObject *parent)
    : QObject(parent)
{
    connect(&ftp, SIGNAL(done(bool)), this, SLOT(ftpDone(bool)));
    connect(&ftp, SIGNAL(listInfo(const QUrlInfo &)),
            this, SLOT(ftpListInfo(const QUrlInfo &)));
}

bool Spider::getDirectory(const QUrl &url)
{
    if (!url.isValid()) {
        std::cerr << "Error: Invalid URL" << std::endl;
        return false;
    }

    if (url.scheme() != "ftp") {
        std::cerr << "Error: URL must start with 'ftp:'" << std::endl;
        return false;
    }

    ftp.connectToHost(url.host(), url.port(21));
    ftp.login();

    QString path = url.path();
    if (path.isEmpty())
        path = "/";

    pendingDirs.append(path);
    processNextDirectory();

    return true;
}

void Spider::ftpDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(ftp.errorString())
                  << std::endl;
    } else {
        std::cout << "Downloaded " << qPrintable(currentDir) << " to "
                  << qPrintable(QDir::toNativeSeparators(
                                QDir(currentLocalDir).canonicalPath()));
    }

    qDeleteAll(openedFiles);
    openedFiles.clear();

    processNextDirectory();
}

void Spider::ftpListInfo(const QUrlInfo &urlInfo)
{
    if (urlInfo.isFile()) {
        if (urlInfo.isReadable()) {
            QFile *file = new QFile(currentLocalDir + "/"
                                    + urlInfo.name());

            if (!file->open(QIODevice::WriteOnly)) {
                std::cerr << "Warning: Cannot write file "
                          << qPrintable(QDir::toNativeSeparators(
                                        file->fileName()))
                          << ": " << qPrintable(file->errorString())
                          << std::endl;
                return;
            }

            ftp.get(urlInfo.name(), file);
            openedFiles.append(file);
        }
    } else if (urlInfo.isDir() && !urlInfo.isSymLink()) {
        pendingDirs.append(currentDir + "/" + urlInfo.name());
    }
}

void Spider::processNextDirectory()
{
    if (!pendingDirs.isEmpty()) {
        currentDir = pendingDirs.takeFirst();
        currentLocalDir = "downloads/" + currentDir;
        QDir(".").mkpath(currentLocalDir);

        ftp.cd(currentDir);
        ftp.list();
    } else {
        emit done();
    }
}
