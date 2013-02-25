#include <QtCore>

#include "booleanparser.h"

Node::Node(Type type, const QString &str)
{
    this->type = type;
    this->str = str;
    parent = 0;
}

Node::~Node()
{
    qDeleteAll(children);
}
