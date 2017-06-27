#ifndef IJOB_H
#define IJOB_H

#include <QObject>
#include <src/logs/Logger.h>

class IJob : public QObject
{
    Q_OBJECT
public:
    explicit IJob(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IJOB_H
