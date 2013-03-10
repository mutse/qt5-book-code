#include <QApplication>
#include <QtWidgets>
#include "weatherstation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WeatherStation station;
    station.show();
    return app.exec();
}
