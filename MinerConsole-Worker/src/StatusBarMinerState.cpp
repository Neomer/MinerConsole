#include "StatusBarMinerState.h"
#include "ui_StatusBarMinerState.h"

StatusBarMinerState::StatusBarMinerState(QWidget *parent) :
	QWidget(parent),
	_miner(0),
	ui(new Ui::StatusBarMinerState)
{
    LOG_TRACE;

    ui->setupUi(this);
	
	_tmr = new QTimer(this);
	connect(_tmr, SIGNAL(timeout()), this, SLOT(updateState()));
	_tmr->setInterval(1000);
	_tmr->start();
}

StatusBarMinerState::~StatusBarMinerState()
{
	delete _tmr;
	delete ui;
}

void StatusBarMinerState::setMiner(Miner *miner)
{
    LOG_TRACE;

    _miner = miner;
	connect(_miner, SIGNAL(stateChanged(QProcess::ProcessState)), 
			this, SLOT(stateChanged(QProcess::ProcessState)));
}

void StatusBarMinerState::updateState()
{
    LOG_TRACE;

    if (_miner)
	{
		if (_miner->isRunning())
		{
			ui->lblState->setText(tr("Work"));
			ui->lblState->setStyleSheet("QLabel { color : #00BB00; font-weight: bold; }");
		}
		else
		{
			ui->lblState->setText(tr("Not running"));
			ui->lblState->setStyleSheet("QLabel { color : #BB0000; font-weight: bold; }");
		}
	}
	else
	{
		ui->lblState->setText(tr("Not running"));
		ui->lblState->setStyleSheet("QLabel { color : #BB0000; font-weight: bold; }");
	}
}

void StatusBarMinerState::stateChanged(QProcess::ProcessState state)
{
    LOG_TRACE;

    switch (state)
	{
		case QProcess::NotRunning:
			ui->lblState->setText(tr("Not running"));
			ui->lblState->setStyleSheet("QLabel { color : #BB0000; font-weight: bold; }");
			break;
			
		case QProcess::Starting:
			ui->lblState->setText(tr("Starting..."));
			ui->lblState->setStyleSheet("QLabel { color : #00BB00; font-weight: bold; }");
			break;
			
		case QProcess::Running:
			ui->lblState->setText(tr("Work"));
			ui->lblState->setStyleSheet("QLabel { color : #00BB00; font-weight: bold; }");
			break;
	}
}
