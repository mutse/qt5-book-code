#include <QApplication>

#include "textartdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TextArtDialog dialog(QObject::tr("Text Art"));
    dialog.resize(600, 300);
    dialog.show();
    return app.exec();
}
