#include <QtWidgets>

#include "cursorhandler.h"
#include "cursorplugin.h"

QStringList CursorPlugin::keys() const
{
    return QStringList() << "cur";
}

QImageIOPlugin::Capabilities
CursorPlugin::capabilities(QIODevice *device,
                           const QByteArray &format) const
{
    if (format == "cur")
        return CanRead;

    if (format.isEmpty()) {
        CursorHandler handler;
        handler.setDevice(device);
        if (handler.canRead())
            return CanRead;
    }

    return 0;
}

QImageIOHandler *CursorPlugin::create(QIODevice *device,
                                      const QByteArray &format) const
{
    CursorHandler *handler = new CursorHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

