#include "Miner.h"

Miner::Miner(QObject *parent) : QObject(parent)
{
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
	stop();
	delete _proc;
}

bool Miner::isRunning()
{
	return _proc->state() == QProcess::Running;
}

bool Miner::start()
{
	_needStop = false;
	_proc->start(getPath(), getArguments().split(' ', QString::SkipEmptyParts), QIODevice::ReadOnly);
	if (!_proc->waitForStarted(5000))
		return false;

	return true;
}

bool Miner::stop()
{
	_needStop = true;
	if (isRunning())
	{
		_proc->terminate();
		if (!_proc->waitForFinished(5000))
			return false;
	}
	return true;
}

void Miner::readStdOut()
{
	QString out(_proc->readAllStandardOutput());
	emit consoleWrite(out);
}

void Miner::readStdError()
{
	QString out(_proc->readAllStandardError());
	emit consoleWrite(out);
}

void Miner::procTerminated()
{
	if (!_needStop)
	{
		qDebug("%s", tr("Proccess unexpectedly terminated! Restart...").toUtf8().constData());
		start();
	}
	else
	{
		qDebug("%s", tr("Proccess successfully terminated!").toUtf8().constData());
	}
}

