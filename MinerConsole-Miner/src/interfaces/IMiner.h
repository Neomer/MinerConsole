#ifndef IMINER_H
#define IMINER_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QThread>

#include <src/interfaces/IJob.h>
#include <src/logs/Logger.h>

class IMiner : public QThread
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

    float hashRate();

protected:
    //virtual void resolve() = 0;
    void appendHashCount() { m_hashes++; }

public slots:
    void start();
    void stop();

signals:
    void hashReady();

private slots:
    void displayHashRate();

private:
    void setState(MinerState value) { m_state = value; }
    void setHashesCount(quint64 value) { m_hashes = value; }
    void resetTime();

    IJob *m_job;
    MinerState m_state;
    quint64 m_hashes;
    qint64 m_start;
    QTimer *m_tmrHashrate;

};

#endif // IMINER_H
