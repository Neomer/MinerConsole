#include "Miner.h"

Miner::Miner(QObject *parent) : QObject(parent)
{
	_proc = new QProcess(this);
	
	connect(_proc, SIGNAL(stateChanged(QProcess::ProcessState)), 
			this, SIGNAL(stateChanged(QProcess::ProcessState)));
}

bool Miner::isRunning()
{
	return _proc->state() == QProcess::Running;
}

bool Miner::start()
{
	_proc->setProgram(getPath());
	_proc->setArguments(getArguments().split(' ', QString::SkipEmptyParts));
	
	_proc->start();
	if (!_proc->waitForStarted(5000))
		return false;
	return true;
}

bool Miner::stop()
{
	_proc->terminate();
	if (!_proc->waitForFinished(5000))
		return false;
	return true;
}

