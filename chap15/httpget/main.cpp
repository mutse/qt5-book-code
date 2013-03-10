#include <QtCore>
#include <iostream>
#include "httpget.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args = QCoreApplication::arguments();

    if (args.count() != 2) {
        std::cerr << "Usage: httpget url" << std::endl
                  << "Example:" << std::endl
                  << "    http://qt-project.org/"
                  << std::endl;
        return 1;
    }

    HttpGet getter;
    if (!getter.getFile(QUrl(args[1])))
        return 1;

    return app.exec();
}
