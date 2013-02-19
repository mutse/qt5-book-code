#include <QApplication>

#include "iconeditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    IconEditor iconEditor;
    iconEditor.setWindowTitle(QObject::tr("Icon Editor"));
    iconEditor.setIconImage(QImage(":/images/mouse.png"));
    iconEditor.show();
    return app.exec();
}
