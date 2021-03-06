#include "MainForm.h"
#include "ui_MainForm.h"

MainForm::MainForm(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainForm)
{
	ui->setupUi(this);
	
	connect(ui->action_Exit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

MainForm::~MainForm()
{
	delete ui;
}
