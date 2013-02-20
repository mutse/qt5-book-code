#include <QtWidgets>
#include <QtXml>
#include <iostream>

void populateTree(QTreeWidget *treeWidget)
{
    QStringList labels;
    labels << QObject::tr("Terms") << QObject::tr("Pages");

    treeWidget->setHeaderLabels(labels);
    treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
    treeWidget->setWindowTitle(QObject::tr("XML Stream Writer"));
    treeWidget->show();

    (void) new QTreeWidgetItem(treeWidget,
            QStringList() << "sidebearings" << "10, 34-35, 307-308");
    QTreeWidgetItem *subterm = new QTreeWidgetItem(treeWidget,
            QStringList() << "subtraction");
    (void) new QTreeWidgetItem(subterm,
            QStringList() << "of pictures" << "115, 244");
    (void) new QTreeWidgetItem(subterm,
            QStringList() << "of vectors" << "9");
}

void writeIndexEntry(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item)
{
    xmlWriter->writeStartElement("entry");
    xmlWriter->writeAttribute("term", item->text(0));
    QString pageString = item->text(1);
    if (!pageString.isEmpty()) {
        QStringList pages = pageString.split(", ");
        foreach (QString page, pages)
            xmlWriter->writeTextElement("page", page);
    }
    for (int i = 0; i < item->childCount(); ++i)
        writeIndexEntry(xmlWriter, item->child(i));
    xmlWriter->writeEndElement();
}

bool writeXml(const QString &fileName, QTreeWidget *treeWidget)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("bookindex");
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
        writeIndexEntry(&xmlWriter, treeWidget->topLevelItem(i));
    xmlWriter.writeEndDocument();

    file.close();
    if (file.error()) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTreeWidget treeWidget;
    populateTree(&treeWidget);
    writeXml("out1.xml", &treeWidget);
    return app.exec();
}
