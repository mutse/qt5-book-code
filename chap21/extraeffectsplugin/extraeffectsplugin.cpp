#include <QtWidgets>

#include "extraeffectsplugin.h"

QStringList ExtraEffectsPlugin::effects() const
{
    return QStringList() << "BigMiddle" << "BigEnds";
}

QPixmap ExtraEffectsPlugin::applyEffect(const QString &effect,
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

    int middle = text.length() / 2;
    qreal x = (size.width() - metrics.width(text)) / 2;
    qreal stepSize = ((myFont.pointSizeF() / 2) / middle) + 1;

    if (effect == "BigEnds") {
        myFont.setPointSizeF(myFont.pointSizeF() + stepSize);
        stepSize = -stepSize;
    } else {
        myFont.setPointSizeF(myFont.pointSizeF() / 2);
    }

    QPainterPath path;
    for (int i = 0; i < text.length(); ++i) {
        QString str(text[i]);
        myFont.setPointSizeF(myFont.pointSizeF() + stepSize);
        QFontMetrics metrics(myFont);
        qreal y = size.height() - metrics.descent()
                  - ((size.height() - metrics.height()) / 2);
        path.addText(x, y, myFont, str);
        x += metrics.width(str) + 1;
        if (i == middle)
            stepSize = -stepSize;
    }
    painter.drawPath(path);

    return pixmap;
}

