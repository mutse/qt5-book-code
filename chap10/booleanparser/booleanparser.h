#ifndef BOOLEANPARSER_H
#define BOOLEANPARSER_H

#include "node.h"

class BooleanParser
{
public:
    Node *parse(const QString &expr);

private:
    Node *parseOrExpression();
    Node *parseAndExpression();
    Node *parseNotExpression();
    Node *parseAtom();
    Node *parseIdentifier();
    void addChild(Node *parent, Node *child);
    void addToken(Node *parent, const QString &str, Node::Type type);
    bool matchToken(const QString &str) const;

    QString in;
    int pos;
};

#endif
