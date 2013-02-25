#include <QtCore>

#include "booleanparser.h"
#include "node.h"

Node *BooleanParser::parse(const QString &expr)
{
    in = expr;
    in.replace(" ", "");
    pos = 0;

    Node *node = new Node(Node::Root);
    addChild(node, parseOrExpression());
    return node;
}

Node *BooleanParser::parseOrExpression()
{
    Node *childNode = parseAndExpression();
    if (matchToken("||")) {
        Node *node = new Node(Node::OrExpression);
        addChild(node, childNode);
        while (matchToken("||")) {
            addToken(node, "||", Node::Operator);
            addChild(node, parseAndExpression());
        }
        return node;
    } else {
        return childNode;
    }
}

Node *BooleanParser::parseAndExpression()
{
    Node *childNode = parseNotExpression();
    if (matchToken("&&")) {
        Node *node = new Node(Node::AndExpression);
        addChild(node, childNode);
        while (matchToken("&&")) {
            addToken(node, "&&", Node::Operator);
            addChild(node, parseNotExpression());
        }
        return node;
    } else {
        return childNode;
    }
}

Node *BooleanParser::parseNotExpression()
{
    if (matchToken("!")) {
        Node *node = new Node(Node::NotExpression);
        while (matchToken("!"))
            addToken(node, "!", Node::Operator);
        addChild(node, parseAtom());
        return node;
    } else {
        return parseAtom();
    }
}

Node *BooleanParser::parseAtom()
{
    if (matchToken("(")) {
        Node *node = new Node(Node::Atom);
        addToken(node, "(", Node::Punctuator);
        addChild(node, parseOrExpression());
        addToken(node, ")", Node::Punctuator);
        return node;
    } else {
        return parseIdentifier();
    }
}

Node *BooleanParser::parseIdentifier()
{
    int startPos = pos;
    while (pos < in.length() && in[pos].isLetterOrNumber())
        ++pos;

    if (pos > startPos) {
        return new Node(Node::Identifier,
                        in.mid(startPos, pos - startPos));
    } else {
        return 0;
    }
}

void BooleanParser::addChild(Node *parent, Node *child)
{
    if (child) {
        parent->children += child;
        parent->str += child->str;
        child->parent = parent;
    }
}

void BooleanParser::addToken(Node *parent, const QString &str,
                             Node::Type type)
{
    if (in.mid(pos, str.length()) == str) {
        addChild(parent, new Node(type, str));
        pos += str.length();
    }
}

bool BooleanParser::matchToken(const QString &str) const
{
    return in.mid(pos, str.length()) == str;
}
