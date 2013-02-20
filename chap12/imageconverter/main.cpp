#include <QApplication>

#include "convertdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ConvertDialog dialog;
    dialog.show();
    return app.exec();
}
