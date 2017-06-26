#ifndef MCCOMMPACKAGE_H
#define MCCOMMPACKAGE_H

#include <QObject>

#include "minerconsole-communication_global.h"
#include "IControllerPoint.h"
#include "TVersion.h"

class MCCommPackage : public IControllerPoint
{
    Q_OBJECT

    Q_PROPERTY(TVersion Version READ Version WRITE setVersion)

public:
    explicit MCCommPackage(QObject *parent = nullptr);
    TVersion Version();

public slots:
    void setVersion(TVersion Version);

private:
    void parse(QByteArray json_array);
    TVersion m_Version;

    // IControllerPoint interface
protected:
    bool dispatch(QString action, QVariant data);
};

#endif // MCCOMMPACKAGE_H
