#include <QtWidgets>
#include <iostream>

#include "saxhandler.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = QApplication::arguments();

    if (args.count() < 2) {
        std::cerr << "Usage: saxhandler file1.xml..." << std::endl;
        return 1;
    }

    QStringList labels;
    labels << QObject::tr("Terms") << QObject::tr("Pages");

    QTreeWidget treeWidget;
    treeWidget.setHeaderLabels(labels);
    treeWidget.header()->setSectionResizeMode(QHeaderView::Stretch);
    treeWidget.setWindowTitle(QObject::tr("SAX Handler"));
    treeWidget.show();

    SaxHandler handler(&treeWidget);
    for (int i = 1; i < args.count(); ++i)
        handler.readFile(args[i]);

    return app.exec();
}
