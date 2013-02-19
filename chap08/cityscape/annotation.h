#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QGraphicsItem>

class Annotation : public QGraphicsItem
{
public:
    Annotation(const QString &text, bool major = false);

    void setText(const QString &text);
    QString text() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QFont font;
    QString str;
    bool major;
    double threshold;
    int y;
};

#endif
