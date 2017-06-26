#ifndef MINERCONSOLECOMMUNICATION_GLOBAL_H
#define MINERCONSOLECOMMUNICATION_GLOBAL_H

#include <QDebug>

#include <QtCore/qglobal.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "Err.h"


#if defined(MINERCONSOLECOMMUNICATION_LIBRARY)
#  define MINERCONSOLE_EXPORT Q_DECL_EXPORT
#else
#  define MINERCONSOLE_EXPORT Q_DECL_IMPORT
#endif

#endif // MINERCONSOLECOMMUNICATION_GLOBAL_H
