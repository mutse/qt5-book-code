#include <QApplication>
#include <QtWidgets>
#include "weatherballoon.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WeatherBalloon balloon;
    balloon.show();
    return app.exec();
}
