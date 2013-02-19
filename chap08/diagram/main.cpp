#include <QApplication>

#include "diagramwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DiagramWindow view;
    view.show();
    return app.exec();
}
