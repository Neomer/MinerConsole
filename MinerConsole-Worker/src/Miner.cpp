#include "Miner.h"

Miner::Miner(QObject *parent) : QObject(parent)
{
    LOG_TRACE;

    _proc = new QProcess(this);
	
	connect(_proc, SIGNAL(stateChanged(QProcess::ProcessState)), 
			this, SIGNAL(stateChanged(QProcess::ProcessState)));
	connect(_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdOut()));
	connect(_proc, SIGNAL(readyReadStandardError()), this, SLOT(readStdError()));
	connect(_proc, SIGNAL(aboutToClose()), this, SLOT(procTerminated()));
	connect(_proc, SIGNAL(finished(int)), this, SLOT(procTerminated()));
}

Miner::~Miner()
{
    LOG_TRACE;

    stop();
	delete _proc;
}

bool Miner::isRunning()
{
	return _proc->state() == QProcess::Running;
}

bool Miner::start()
{
    LOG_TRACE;

    if (!QFile::exists(getPath()))
    {
        LOG_WARN << tr("File not found!") << getPath();
        return false;
    }

    _needStop = false;
	_proc->start(getPath(), getArguments().split(' ', QString::SkipEmptyParts), QIODevice::ReadOnly);
	if (!_proc->waitForStarted(5000))
    {
        LOG_WARN << "Process starting failed!";
        return false;
    }

	return true;
}

bool Miner::stop()
{
    LOG_TRACE;

    _needStop = true;
	if (isRunning())
	{
		_proc->terminate();
		if (!_proc->waitForFinished(5000))
        {
            LOG_WARN << "Process terminating failed!";
            return false;
        }
    }
    else
    {
        LOG_DEBUG << tr("Process already stopped!");
    }
	return true;
}

void Miner::readStdOut()
{
    LOG_TRACE;

    QString out(_proc->readAllStandardOutput());
	emit consoleWrite(out);
}

void Miner::readStdError()
{
    LOG_TRACE;

    QString out(_proc->readAllStandardError());
	emit consoleWrite(out);
}

void Miner::procTerminated()
{
    LOG_TRACE;

    if (!_needStop)
	{
        LOG_WARN << tr("Proccess unexpectedly terminated! Restart...");
		start();
	}
	else
	{
        LOG_DEBUG << tr("Proccess unexpectedly terminated!");
	}
}

