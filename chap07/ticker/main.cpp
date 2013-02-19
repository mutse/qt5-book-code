#include <QApplication>

#include "ticker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Ticker ticker;
    ticker.setWindowTitle(QObject::tr("Ticker"));
    ticker.setText(QObject::tr("How long it lasted was impossible to "
                               "say ++ "));
    ticker.show();
    return app.exec();
}
