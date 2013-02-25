#include <QApplication>

#include "booleanwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BooleanWindow window;
    window.show();
    return app.exec();
}
