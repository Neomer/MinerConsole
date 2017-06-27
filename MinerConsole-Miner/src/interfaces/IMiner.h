#ifndef IMINER_H
#define IMINER_H

#include <QObject>
#include <src/interfaces/IJob.h>
#include <src/logs/Logger.h>

class IMiner : public QObject
{
    Q_OBJECT
public:
    enum MinerState
    {
        MinerState_Stop,
        MinerState_Run
    };

    explicit IMiner(QObject *parent = nullptr);

    void setJob(IJob *value) { m_job = value; }
    IJob *currentJob() { return m_job; }

    MinerState state() { return m_state; }

public slots:
    void start();
    void stop();

signals:
    void hashReady();

private:
    void setState(MinerState value) { m_state = value; }

    IJob *m_job;
    MinerState m_state;
};

#endif // IMINER_H
