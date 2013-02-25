#include <QtWidgets>

#include "bronzestyleplugin.h"
#include "../bronze/bronzestyle.h"

QStringList BronzeStylePlugin::keys() const
{
    return QStringList() << "Bronze";
}

QStyle *BronzeStylePlugin::create(const QString &key)
{
    if (key.toLower() == "bronze")
        return new BronzeStyle;
    return 0;
}

