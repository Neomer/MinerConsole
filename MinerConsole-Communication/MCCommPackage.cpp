#include "MCCommPackage.h"
#include <QMetaObject>
#include <QMetaProperty>

MCCommPackage::MCCommPackage(QObject *parent) : QObject(parent)
{

}

TVersion MCCommPackage::Version() const
{
    return m_Version;
}

void MCCommPackage::setVersion(TVersion Version)
{
    m_Version = Version;
}

void MCCommPackage::parse(QByteArray json_array)
{
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(json_array, &err);
    const QMetaObject *mo = this->metaObject();
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i)
    {
        QJsonValue val = json.object()[mo->property(i).name()];
        if (val.isUndefined())
        {
            continue;
        }
    }
}
