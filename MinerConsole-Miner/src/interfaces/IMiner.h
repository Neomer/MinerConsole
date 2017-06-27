#ifndef IMINER_H
#define IMINER_H

#include <QObject>
#include <src/interfaces/IJob.h>
#include <src/logs/Logger.h>

class IMiner : public QObject
{
    Q_OBJECT
public:
    explicit IMiner(QObject *parent = nullptr);

    void setJob(IJob *value) { m_job = value; }
    IJob *currentJob() { return m_job; }

public slots:
    void start();

signals:
    void hashReady();

private:
    IJob *m_job;
};

#endif // IMINER_H
