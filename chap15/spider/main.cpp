#include <QtCore>
#include <iostream>

#include "spider.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args = QCoreApplication::arguments();

    if (args.count() != 2) {
        std::cerr << "Usage: spider url" << std::endl
                  << "Example:" << std::endl
                  << "    spider ftp://ftp.trolltech.com/freebies/"
                  << "leafnode" << std::endl;
        return 1;
    }

    Spider spider;
    if (!spider.getDirectory(QUrl(args[1])))
        return 1;

    QObject::connect(&spider, SIGNAL(done()), &app, SLOT(quit()));

    return app.exec();
}
