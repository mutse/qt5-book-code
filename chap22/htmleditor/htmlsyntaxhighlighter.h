#ifndef HTMLSYNTAXHIGHLIGHTER_H
#define HTMLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class HtmlSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum Construct {
        Entity,
        Tag,
        Comment,
        LastConstruct = Comment
    };

    HtmlSyntaxHighlighter(QTextDocument *document);

    void setFormatFor(Construct construct,
                      const QTextCharFormat &format);
    void setFormatFor(Construct construct,
                      const QColor &color);
    void setFormatFor(Construct construct,
                      const QFont &font);
    QTextCharFormat formatFor(Construct construct) const
        { return formats[construct]; }

protected:
    enum State {
        NormalState = -1,
        InComment,
        InTag
    };

    void highlightBlock(const QString &text);

private:
    QTextCharFormat formats[LastConstruct + 1];
};

#endif
