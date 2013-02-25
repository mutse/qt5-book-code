#include <QtWidgets>

#include "bronzedialog.h"
#include "bronzestyle.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle(new BronzeStyle);
    BronzeDialog dialog;
    dialog.layout()->setSpacing(7);
    dialog.layout()->setMargin(7);
    dialog.show();
    return app.exec();
}
