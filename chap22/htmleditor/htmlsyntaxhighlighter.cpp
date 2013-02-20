#include <QtWidgets>

#include "htmlsyntaxhighlighter.h"

HtmlSyntaxHighlighter::HtmlSyntaxHighlighter(QTextDocument *document)
    : QSyntaxHighlighter(document)
{
    QTextCharFormat entityFormat;
    entityFormat.setForeground(QColor(0, 128, 0));
    entityFormat.setFontWeight(QFont::Bold);
    setFormatFor(Entity, entityFormat);

    QTextCharFormat tagFormat;
    tagFormat.setForeground(QColor(192, 16, 112));
    tagFormat.setFontWeight(QFont::Bold);
    setFormatFor(Tag, tagFormat);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor(128, 10, 74));
    commentFormat.setFontItalic(true);
    setFormatFor(Comment, commentFormat);
}

void HtmlSyntaxHighlighter::setFormatFor(Construct construct,
                                         const QTextCharFormat &format)
{
    formats[construct] = format;
    rehighlight();
}

void HtmlSyntaxHighlighter::setFormatFor(Construct construct,
                                         const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(color);
    setFormatFor(construct, format);
}

void HtmlSyntaxHighlighter::setFormatFor(Construct construct,
                                         const QFont &font)
{
    QTextCharFormat format;
    format.setFont(font);
    setFormatFor(construct, format);
}

void HtmlSyntaxHighlighter::highlightBlock(const QString &text)
{
    int state = previousBlockState();
    int len = text.length();
    int start = 0;
    int pos = 0;

    while (pos < len) {
        switch (state) {
        case NormalState:
        default:
            while (pos < len) {
                QChar ch = text.at(pos);
                if (ch == '<') {
                    if (text.mid(pos, 4) == "<!--") {
                        state = InComment;
                    } else {
                        state = InTag;
                    }
                    break;
                } else if (ch == '&') {
                    start = pos;
                    while (pos < len && text.at(pos++) != ';')
                        ;
                    setFormat(start, pos - start, formats[Entity]);
                } else {
                    ++pos;
                }
            }
            break;
        case InComment:
            start = pos;
            while (pos < len) {
                if (text.mid(pos, 3) == "-->") {
                    pos += 3;
                    state = NormalState;
                    break;
                } else {
                    ++pos;
                }
            }
            setFormat(start, pos - start, formats[Comment]);
            break;
        case InTag:
            QChar openQuote;
            start = pos;
            while (pos < len) {
                QChar ch = text.at(pos);
                if (openQuote.isNull()) {
                    if (ch == '\'' || ch == '"') {
                        openQuote = ch;
                    } else if (ch == '>') {
                        ++pos;
                        state = NormalState;
                        break;
                    }
                } else if (ch == openQuote) {
                    openQuote = QChar();
                }
                ++pos;
            }
            setFormat(start, pos - start, formats[Tag]);
        }
    }

    setCurrentBlockState(state);
}
