#include <QtWidgets>

#include "basiceffectsplugin.h"

QStringList BasicEffectsPlugin::effects() const
{
    return QStringList() << "Plain" << "Outline" << "Shadow";
}

QPixmap BasicEffectsPlugin::applyEffect(const QString &effect,
        const QString &text, const QFont &font, const QSize &size,
        const QPen &pen, const QBrush &brush)
{
    QFont myFont = font;
    QFontMetrics metrics(myFont);
    while ((metrics.width(text) > size.width()
            || metrics.height() > size.height())
           && myFont.pointSize() > 9) {
        myFont.setPointSize(myFont.pointSize() - 1);
        metrics = QFontMetrics(myFont);
    }

    QPixmap pixmap(size);

    QPainter painter(&pixmap);
    painter.setFont(myFont);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.eraseRect(pixmap.rect());

    if (effect == "Plain") {
        painter.setPen(Qt::NoPen);
    } else if (effect == "Outline") {
        QPen pen(Qt::black);
        pen.setWidthF(2.5);
        painter.setPen(pen);
    } else if (effect == "Shadow") {
        QPainterPath path;
        painter.setBrush(Qt::darkGray);
        path.addText(((size.width() - metrics.width(text)) / 2) + 3,
                     (size.height() - metrics.descent()) + 3, myFont,
                     text);
        painter.drawPath(path);
        painter.setBrush(brush);
    }

    QPainterPath path;
    path.addText((size.width() - metrics.width(text)) / 2,
                 size.height() - metrics.descent(), myFont, text);
    painter.drawPath(path);

    return pixmap;
}

