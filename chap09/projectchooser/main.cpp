#include <QtGui>

#include "projectdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ProjectDialog dialog;
    dialog.show();
    return app.exec();
}
