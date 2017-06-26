#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QObject>
#include <QHash>
#include <boost/serialization/singleton.hpp>

#include "IControllerPoint.h"
#include "Err.h"

class IController : public QObject
{
    Q_OBJECT

public:
    explicit IController(IController *parent = 0);

    IController *parent() { return _parent; }

    void subscribe(QString path, IControllerPoint *point);
    void dispatch(QString path, QString action, QVariant data);

private:
    void setParent(IController *value) { _parent = value; }

    QHash<QString, IControllerPoint *> _map;
    IController *_parent;
};

#endif // ICONTROLLER_H
