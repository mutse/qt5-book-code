#ifndef CITYBLOCK_H
#define CITYBLOCK_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>

QT_BEGIN_NAMESPACE
class QGradient;
QT_END_NAMESPACE

class CityBlock : public QGraphicsItem
{
public:
    enum Kind { Park, SmallBuilding, Hospital, Hall, Building, Tower,
                LShapedBlock, LShapedBlockPlusSmallBlock, TwoBlocks,
                BlockPlusTwoSmallBlocks };

    CityBlock(Kind kind);

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int kind;
    QColor color;
    QPainterPath shape;
};

#endif
