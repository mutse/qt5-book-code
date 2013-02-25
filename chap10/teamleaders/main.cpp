#include <QApplication>

#include "teamleadersdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringList leaders;
    leaders << "Stooge Viller" << "Littleface" << "B-B Eyes"
            << "Pruneface" << "Mrs. Pruneface" << "The Brow"
            << "Vitamin Flintheart" << "Flattop Sr." << "Shakey"
            << "Breathless Mahoney" << "Mumbles" << "Shoulders"
            << "Sketch Paree";

    TeamLeadersDialog dialog(leaders);
    dialog.show();

    return app.exec();
}
