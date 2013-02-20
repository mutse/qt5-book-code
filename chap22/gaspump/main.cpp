#include <QApplication>
#include <iostream>

#include "pumpwindow.h"
#include "scripting.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = QApplication::arguments();
    if (args.count() >= 3 && args[1] == "-script") {
        runScript(args[2], args.mid(3));
        return 0;
    } else if (args.count() == 1) {
        PumpWindow window;
        window.show();
        window.resize(600, 400);
        return app.exec();
    } else {
        std::cerr << "Usage: gaspump [-script myscript.js <arguments>]"
                  << std::endl;
        return 1;
    }
}
