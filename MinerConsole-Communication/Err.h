#ifndef ERR_H
#define ERR_H

#include <QDebug>

#define LOG_TRACE                   qDebug() << Q_FUNC_INFO

#define E_WRONG_FORMAT              tr("WrongFormat")

#endif // ERR_H
