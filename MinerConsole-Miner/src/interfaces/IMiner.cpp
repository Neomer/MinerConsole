#include "IMiner.h"

IMiner::IMiner(QObject *parent) : QThread(parent)
{
    LOG_TRACE;

    setJob(0);
    setState(MinerState_Stop);
    setHashesCount(0);

    m_tmrHashrate = new QTimer(this);
    m_tmrHashrate->setInterval(5000);

    connect(m_tmrHashrate, SIGNAL(timeout()), this, SLOT(displayHashRate()));
}

float IMiner::hashRate()
{
    qint64 msecs = QDateTime::currentSecsSinceEpoch() - m_start;
    quint64 hashes = m_hashes;
    resetTime();
    setHashesCount(0);
    return hashes / msecs;
}

void IMiner::start()
{
    LOG_TRACE;

    if (!currentJob())
    {
        LOG_DEBUG << tr("Job is empty");
        return;
    }
    resetTime();
    m_tmrHashrate->start();
    setState(MinerState_Run);
    QThread::start(QThread::HighPriority);
}

void IMiner::stop()
{
    LOG_TRACE;
    m_tmrHashrate->stop();
}

void IMiner::displayHashRate()
{
    LOG_DEBUG << hashRate() << "hash/sec";
}

void IMiner::resetTime()
{
    LOG_TRACE;

    m_start = QDateTime::currentSecsSinceEpoch();
}
