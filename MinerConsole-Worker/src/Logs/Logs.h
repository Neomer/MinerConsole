#ifndef LOGS_H
#define LOGS_H

#include <QDebug>
#include <QDateTime>

#define LOG_TRACE                   qDebug() << "TRACE" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_DEBUG                   qDebug() << "DEBUG" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO
#define LOG_WARN                    qDebug() << "WARN " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << Q_FUNC_INFO

#define E_WRONG_FORMAT              tr("WrongFormat")

#endif // LOGS_H
