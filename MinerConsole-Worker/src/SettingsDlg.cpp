#include "SettingsDlg.h"
#include "ui_SettingsDlg.h"

SettingsDlg::SettingsDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDlg)
{
	ui->setupUi(this);
	
	connect(ui->pbCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
	connect(ui->pbSave, SIGNAL(clicked(bool)), this, SLOT(saveSettings()));
}

SettingsDlg::~SettingsDlg()
{
	delete ui;
}

void SettingsDlg::saveSettings()
{
	this->accept();
}
