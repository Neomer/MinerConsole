#ifndef MCCOMMPACKAGE_H
#define MCCOMMPACKAGE_H

#include <QObject>
#include "minerconsole-communication_global.h"
#include "TVersion.h"

class MCCommPackage : public QObject
{
    Q_OBJECT

public:
    explicit MCCommPackage(QObject *parent = nullptr);

private:
    void parse(QByteArray ba);
};

#endif // MCCOMMPACKAGE_H
