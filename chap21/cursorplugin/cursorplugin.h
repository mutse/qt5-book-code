#ifndef CURSORPLUGIN_H
#define CURSORPLUGIN_H

#include <QImageIOPlugin>

class CursorPlugin : public QImageIOPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QImageIOFactoryInterface" FILE "cursor.json")
public:
    QStringList keys() const;
    Capabilities capabilities(QIODevice *device,
                              const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device,
                            const QByteArray &format) const;
};

#endif
