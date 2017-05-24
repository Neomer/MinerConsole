#ifndef STATUSBARMINERSTATE_H
#define STATUSBARMINERSTATE_H

#include <QWidget>
#include <QTimer>
#include "Miner.h"

namespace Ui {
	class StatusBarMinerState;
}

class StatusBarMinerState : public QWidget
{
	Q_OBJECT
	
public:
	explicit StatusBarMinerState(QWidget *parent = 0);
	~StatusBarMinerState();
	
	void setMiner(Miner *miner);
	
private slots:
	void updateState();
	void stateChanged(QProcess::ProcessState state);
	
private:
	Ui::StatusBarMinerState *ui;
	QTimer *_tmr;
	Miner * _miner;
};

#endif // STATUSBARMINERSTATE_H
