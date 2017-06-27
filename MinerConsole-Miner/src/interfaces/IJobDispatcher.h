#ifndef IJOBDISPATCHER_H
#define IJOBDISPATCHER_H

#include <QObject>
#include <src/interfaces/IJob.h>
#include <src/logs/Logger.h>

class IJobDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit IJobDispatcher(QObject *parent = nullptr);

signals:
    void jobReceived(IJob *job);

public slots:
};

#endif // IJOBDISPATCHER_H
