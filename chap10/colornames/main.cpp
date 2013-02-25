#include <QApplication>

#include "colornamesdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ColorNamesDialog dialog;
    dialog.show();
    return app.exec();
}
