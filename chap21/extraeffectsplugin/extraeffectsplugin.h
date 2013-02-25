#ifndef BASICEFFECTSPLUGIN_H
#define BASICEFFECTSPLUGIN_H

#include <QObject>

#include "../textart/textartinterface.h"

class ExtraEffectsPlugin : public QObject, public TextArtInterface
{
    Q_OBJECT
	Q_PLUGIN_METADATA(IID "com.software-inc.TextArt.TextArtInterface/1.0" FILE "extraeffectsplugin.json")
    Q_INTERFACES(TextArtInterface)

public:
    QStringList effects() const;
    QPixmap applyEffect(const QString &effect, const QString &text,
                        const QFont &font, const QSize &size,
                        const QPen &pen, const QBrush &brush);
};

#endif
