#include <QApplication>

#include "cityscape.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Cityscape cityscape;
    cityscape.show();
    return app.exec();
}
