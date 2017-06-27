#include "IMiner.h"

IMiner::IMiner(QObject *parent) : QObject(parent)
{
    LOG_TRACE;

    setState(MinerState_Stop);
}

void IMiner::start()
{
    LOG_TRACE;
}

void IMiner::stop()
{
    LOG_TRACE;
}
