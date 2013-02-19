#include <QtWidgets>
#include <cmath>

#include "cityblock.h"

CityBlock::CityBlock(Kind kind)
{
    this->kind = kind;

    int green = 96 + (std::rand() % 64);
    int red = 16 + green + (std::rand() % 64);
    int blue = 16 + (std::rand() % green);
    color = QColor(red, green, blue);

    if (kind == Park) {
        color = QColor(192 + (std::rand() % 32), 255,
                       192 + (std::rand() % 16));
        shape.addRect(boundingRect());
    } else if (kind == SmallBuilding) {
        QRectF block(-7.5, -7.5, 15, 15);
        block.moveBottomLeft(QPointF((std::rand() % 6) - 3,
                                     (std::rand() % 6) - 3));
        shape.addRect(block);
    } else if (kind == Hospital) {
        int a = (std::rand() % 6) + 10;
        int b = (std::rand() % 6) + 10;
        QPolygonF block;
        block << QPointF(-5, -a) << QPointF(-5, -5) << QPointF(-10, -5)
              << QPointF(-10, 5) << QPointF(-5, 5)  << QPointF(-5, 10)
              << QPointF(5, 10)  << QPointF(5, 5)   << QPointF(b, 5)
              << QPointF(b, -5)  << QPointF(5, -5)  << QPointF(5, -a);
        shape.addPolygon(block);
    } else if (kind == Hall) {
        int padding1 = (std::rand() % 8) + 2;
        int padding2 = (std::rand() % 8) + 2;
        shape.addEllipse(boundingRect().adjusted(+padding1, +padding1,
                                                 -padding2, -padding2));
    } else if (kind == Building) {
        shape.addRect(boundingRect());
    } else if (kind == Tower) {
        int padding1 = (std::rand() % 8) + 2;
        int padding2 = (std::rand() % 8) + 2;
        shape.addRect(boundingRect().adjusted(+padding1, +padding1,
                                              -padding2, -padding2));
    } else if (kind == LShapedBlock
               || kind == LShapedBlockPlusSmallBlock) {
        int a = (std::rand() % 6) + 10;
        int b = (std::rand() % 6) + 10;
        int s = qMin(a, b) / 2;
        QPolygonF block;
        block << QPointF(-a, -a) << QPointF(-a, +a) << QPointF(-s, +a)
              << QPointF(-s, -s) << QPointF(+b, -s) << QPointF(+b, -a);
        shape.addPolygon(block);
        if (kind == LShapedBlockPlusSmallBlock) {
            int inset = (std::rand() % 4) + 4;
            shape.addRect(QRectF(-s + inset, -s + inset, a, b));
        }
    } else if (kind == TwoBlocks) {
        int w1 = (std::rand() % 10) + 8;
        int h1 = (std::rand() % 28) + 8;
        int w2 = (std::rand() % 10) + 8;
        int h2 = (std::rand() % 24) + 8;
        shape.addRect(QRectF(-16, -16, w1, h1));
        shape.addRect(QRectF(-16 + w1 + 4, -16 + (std::rand() % 4),
                             w2, h2));
    } else if (kind == BlockPlusTwoSmallBlocks) {
        int w1 = (std::rand() % 10) + 8;
        int h1 = (std::rand() % 28) + 8;
        int w2 = (std::rand() % 10) + 8;
        int h2 = (std::rand() % 10) + 8;
        int w3 = (std::rand() % 6) + 8;
        int h3 = (std::rand() % 6) + 8;
        int y = (std::rand() % 4) - 16;
        shape.addRect(QRectF(-16, -16, w1, h1));
        shape.addRect(QRectF(-16 + w1 + 4, y, w2, h2));
        shape.addRect(QRectF(-16 + w1 + 4,
                             y + h2 + 4 + (std::rand() % 4), w3, h3));
    }
}

QRectF CityBlock::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

void CityBlock::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget * /* widget */)
{
    if (option->levelOfDetail < 4.0) {
        painter->fillPath(shape, color);
    } else {
        QLinearGradient gradient(QPoint(-20, -20), QPoint(+20, +20));
        int coeff = 105 + int(std::log(option->levelOfDetail - 4.0));
        gradient.setColorAt(0.0, color.lighter(coeff));
        gradient.setColorAt(1.0, color.darker(coeff));
        painter->fillPath(shape, gradient);
    }
}
