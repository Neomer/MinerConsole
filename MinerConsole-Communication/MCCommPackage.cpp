#include "MCCommPackage.h"
#include <QMetaObject>
#include <QMetaProperty>

MCCommPackage::MCCommPackage(QObject *parent) :
    IControllerPoint(parent)
{

}

TVersion MCCommPackage::Version()
{
    return m_Version;
}

void MCCommPackage::setVersion(TVersion Version)
{
    m_Version = Version;
}

void MCCommPackage::parse(QByteArray json_array)
{
    LOG_TRACE;

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

bool MCCommPackage::dispatch(QString action, QVariant data)
{
    LOG_TRACE << action << data;
    return true;
}
