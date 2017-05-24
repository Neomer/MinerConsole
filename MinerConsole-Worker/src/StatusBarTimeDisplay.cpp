#include "StatusBarTimeDisplay.h"
#include "ui_StatusBarTimeDisplay.h"

StatusBarTimeDisplay::StatusBarTimeDisplay(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StatusBarTimeDisplay)
{
	ui->setupUi(this);

	ui->lblTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	
	_tmr = new QTimer(this);
	connect(_tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
	
	_tmr->setInterval(1000);
	_tmr->start();
}

StatusBarTimeDisplay::~StatusBarTimeDisplay()
{
	delete _tmr;
	delete ui;
}

void StatusBarTimeDisplay::updateTime()
{
	ui->lblTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}
