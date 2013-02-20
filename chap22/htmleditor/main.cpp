#include <QtWidgets>

#include "htmlwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    HtmlWindow window;
    window.show();
    return app.exec();
}
