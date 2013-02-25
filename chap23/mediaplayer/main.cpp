#include <QApplication>

#include "playerwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PlayerWindow playerWin;
    playerWin.show();
    return app.exec();
}
