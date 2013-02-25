#include <QApplication>

#include "trackeditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QList<Track> tracks;
    tracks << Track("The Flying Dutchman: Overture", 630)
           << Track("The Flying Dutchman: Wie aus der Fern laengst "
                    "vergangner Zeiten", 374)
           << Track("The Flying Dutchman: Steuermann, lass die Wacht",
                    152)
           << Track("Die Walkuere: Ride of the Valkyries", 286)
           << Track("Tannhaeuser: Freudig begruessen wir die edle "
                    "Halle", 384)
           << Track("Tannhaeuser: Wie Todesahnung - O du mein holder "
                    "Abendstern", 257)
           << Track("Lohengrin: Treulich gefuert ziehet dahnin", 294)
           << Track("Lohengrin: In fernem Land", 383)
           << Track("Die Meistersinger von Nuernberg: Overture", 543)
           << Track("Die Meistersinger von Nuernberg: Verachtet mir "
                    "die Meister nicht", 200)
           << Track("Die Meistersinger von Nuernberg: Ehrt eure "
                    "deutschen Meister", 112)
           << Track("Goetterdaemmerung: Funeral Music", 469)
           << Track("Tristan und Isolde: Mild und leise, wie er "
                    "laechelt", 375);

    TrackEditor editor(&tracks);
    editor.resize(600, 300);
    editor.show();

    return app.exec();
}
