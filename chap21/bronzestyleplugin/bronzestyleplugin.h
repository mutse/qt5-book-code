#ifndef BRONZESTYLEPLUGIN_H
#define BRONZESTYLEPLUGIN_H

#include <QStylePlugin>

class BronzeStylePlugin : public QStylePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "bronzestyle.json")
public:
    QStringList keys() const;
    QStyle *create(const QString &key);
};

#endif
