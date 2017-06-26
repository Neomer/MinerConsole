#include "Coin.h"

Coin::Coin(QJsonObject object, QObject *parent) :
    QObject(parent)
{
    setShortName(object["shortname"].toString());
    setName(object["name"].toString());
    setIcon(QIcon(qApp->applicationDirPath().append("/").append(object["icon"].toString())));
}
