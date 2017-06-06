#include "SettingsDlg.h"
#include "ui_SettingsDlg.h"
#include <QTableWidgetItem>

SettingsDlg::SettingsDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDlg)
{
	ui->setupUi(this);
	
	connect(ui->pbCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
	connect(ui->pbSave, SIGNAL(clicked(bool)), this, SLOT(saveSettings()));
	connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(listIndexChanged(int))); 
	
	for (int i = 0; i < Settings::instance().miners().count(); i++)
	{
		ui->listWidget->addItem(QString("%1 [%2]").arg(
									Settings::instance().miners().at(i).toObject()["name"].toString(),
									Settings::instance().miners().at(i).toObject()["type"].toString()
								));
	}
	
}

SettingsDlg::~SettingsDlg()
{
	delete ui;
}

void SettingsDlg::saveSettings()
{
	this->accept();
}

void SettingsDlg::listIndexChanged(int index)
{
	QJsonObject obj = Settings::instance().minerByType(Settings::instance().miners().at(index).toObject()["type"].toString());
	QJsonArray args = obj["args"].toArray();
	ui->tableWidget->setRowCount(args.count());
	for (int i = 0; i < args.count(); i++)
	{
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(args.at(i).toObject()["desciption"].toString()));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(args.at(i).toObject()["name"].toString()));
	}
}
