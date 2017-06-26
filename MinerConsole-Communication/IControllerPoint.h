#ifndef ICONTROLLERPOINT_H
#define ICONTROLLERPOINT_H

#include <QObject>

class IControllerPoint : public QObject
{
    Q_OBJECT

    friend class IController;

public:
    IControllerPoint(QObject *parent = 0) : QObject(parent) {}

protected:
    virtual bool dispatch(QString action, QVariant data) = 0;
};

#endif // ICONTROLLERPOINT_H
