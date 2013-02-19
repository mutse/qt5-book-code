#ifndef LINK_H
#define LINK_H

#include <QGraphicsLineItem>

QT_BEGIN_NAMESPACE
class Node;
QT_END_NAMESPACE

class Link : public QGraphicsLineItem
{
public:
    Link(Node *fromNode, Node *toNode);
    ~Link();

    Node *fromNode() const;
    Node *toNode() const;

    void setColor(const QColor &color);
    QColor color() const;

    void trackNodes();

private:
    Node *myFromNode;
    Node *myToNode;
};

#endif
