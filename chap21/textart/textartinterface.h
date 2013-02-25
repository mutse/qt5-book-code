#ifndef TEXTARTINTERFACE_H
#define TEXTARTINTERFACE_H

QT_BEGIN_NAMESPACE
class QBrush;
class QFont;
class QPen;
class QPixmap;
class QSize;
class QString;
class QStringList;
QT_END_NAMESPACE

class TextArtInterface
{
public:
    virtual ~TextArtInterface() { }

    virtual QStringList effects() const = 0;
    virtual QPixmap applyEffect(const QString &effect,
                                const QString &text,
                                const QFont &font, const QSize &size,
                                const QPen &pen,
                                const QBrush &brush) = 0;
};

Q_DECLARE_INTERFACE(TextArtInterface,
                    "com.software-inc.TextArt.TextArtInterface/1.0")

#endif
