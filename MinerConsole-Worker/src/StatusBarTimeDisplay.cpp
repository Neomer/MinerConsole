#include "StatusBarTimeDisplay.h"
#include "ui_StatusBarTimeDisplay.h"

StatusBarTimeDisplay::StatusBarTimeDisplay(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StatusBarTimeDisplay)
{
    LOG_TRACE;

    ui->setupUi(this);

	ui->lblTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	
	_tmr = new QTimer(this);
	connect(_tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
	
	_tmr->setInterval(1000);
	_tmr->start();
}

StatusBarTimeDisplay::~StatusBarTimeDisplay()
{
    LOG_TRACE;

    delete _tmr;
	delete ui;
}

void StatusBarTimeDisplay::updateTime()
{
    LOG_TRACE;

    ui->lblTime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}
