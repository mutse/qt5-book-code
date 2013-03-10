#ifndef SPIDER_H
#define SPIDER_H

#include <QFtp>
#include <QStringList>

class QFile;

class Spider : public QObject
{
    Q_OBJECT

public:
    Spider(QObject *parent = 0);

    bool getDirectory(const QUrl &url);

signals:
    void done();

private slots:
    void ftpDone(bool error);
    void ftpListInfo(const QUrlInfo &urlInfo);

private:
    void processNextDirectory();

    QFtp ftp;
    QList<QFile *> openedFiles;
    QString currentDir;
    QString currentLocalDir;
    QStringList pendingDirs;
};

#endif
