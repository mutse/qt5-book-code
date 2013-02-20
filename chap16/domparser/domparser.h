#ifndef DOMPARSER_H
#define DOMPARSER_H

QT_BEGIN_NAMESPACE
class QDomElement;
class QString;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class DomParser
{
public:
    DomParser(QTreeWidget *tree);

    bool readFile(const QString &fileName);

private:
    void parseBookindexElement(const QDomElement &element);
    void parseEntryElement(const QDomElement &element,
                           QTreeWidgetItem *parent);
    void parsePageElement(const QDomElement &element,
                          QTreeWidgetItem *parent);

    QTreeWidget *treeWidget;
};

#endif
