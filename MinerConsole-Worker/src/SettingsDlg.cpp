#include "SettingsDlg.h"
#include "ui_SettingsDlg.h"
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QComboBox>

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
		QJsonObject miner = Settings::instance().miners().at(i).toObject();
		
		QListWidgetItem *lwi = new QListWidgetItem(QString("%1 [%2]").arg(
													  miner["name"].toString(),
													  miner["type"].toString()
												  ));
		lwi->setData(Qt::UserRole, miner["name"].toString());
		ui->listWidget->addItem(lwi);
	}
	
}

SettingsDlg::~SettingsDlg()
{
	delete ui;
}

void SettingsDlg::saveSettings()
{
	qDebug() << "SettingsDlg::saveSettings()";
	
	QJsonObject miner = Settings::instance().minerByName(ui->listWidget->currentItem()->data(Qt::UserRole).toString());
	QJsonObject settings = miner["settings"].toObject();
	QJsonArray sm = Settings::instance().supportedMinerByType(miner["type"].toString())["args"].toArray();
	for (int i = 0; i < ui->tableWidget->rowCount(); i++)
	{
		QString name = ui->tableWidget->item(i, 0)->data(Qt::UserRole).toString();
		QString type;
		
		for (int i = 0; i < sm.count(); i++)
		{
			if (sm.at(i).toObject()["name"] == name)
			{
				type = sm.at(i).toObject()["type"].toString();
				sm.removeAt(i);
				break;
			}
		}
		
		bool ok;
		if (type == "int")
		{
			if (!ui->tableWidget->item(i, 1)->text().isEmpty())
			{
				settings[name] = ui->tableWidget->item(i, 1)->text().toInt(&ok);
				if (!ok)
				{
					throw std::runtime_error(tr("Wrong value's format in row ").append(QString::number(i + 1)).toStdString());
					return;
				}
			}
		}
		else if (type == "bool")
		{
			QComboBox * cmb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(i, 1));
			if ( cmb->currentText() == "true" )
			{
				settings[name] = 1;
			}
			else
			{
				settings[name] = 0;
			}
		}
		else if (type == "enum")
		{
			QComboBox * cmb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(i, 1));
			settings[name] = cmb->currentData(Qt::UserRole).toString();
		}
		else
		{
			settings[name] = ui->tableWidget->item(i, 1)->text();
		}
		qDebug() << name 
				 << type
				 << settings[name];
	}
	Settings::instance().setMinerSettings(miner["name"].toString(), settings);
	Settings::instance().save();
	
	this->accept();
}

void SettingsDlg::listIndexChanged(int index)
{
	qDebug() << "SettingsDlg::listIndexChanged(int)";

	QJsonObject miner = Settings::instance().minerByName(ui->listWidget->currentItem()->data(Qt::UserRole).toString());
	QJsonObject obj = Settings::instance().supportedMinerByType(Settings::instance().miners().at(index).toObject()["type"].toString());
	QJsonArray args = obj["args"].toArray();
	ui->tableWidget->setRowCount(args.count());
	for (int i = 0; i < args.count(); i++)
	{
		QString type = args.at(i).toObject()["type"].toString();
		
		QTableWidgetItem *twi = new QTableWidgetItem(args.at(i).toObject()["desciption"].toString());
		twi->setToolTip(args.at(i).toObject()["help"].toString());
		twi->setData(Qt::UserRole, args.at(i).toObject()["name"].toString());
		ui->tableWidget->setItem(i, 0, twi);
		
		QJsonValueRef valRef = miner["settings"].toObject()[args.at(i).toObject()["name"].toString()];
		qDebug() << args.at(i).toObject()["name"].toString()
				<< miner["settings"].toObject()[args.at(i).toObject()["name"].toString()]
				<< type;		
		QString value;
		twi = new QTableWidgetItem();
		
		if (valRef.isNull() || 
				valRef.isUndefined())
		{
			value = args.at(i).toObject()["default"].toString();
		}
		else
		{
			value = valRef.toVariant().toString();
		}
		twi->setToolTip(args.at(i).toObject()["help"].toString());

		if (type == "enum")
		{
			QJsonArray arr = args.at(i).toObject()["default"].toArray();
			QComboBox *cmb = new QComboBox(ui->tableWidget);
			int idx = 0;
			for (int i = 0; i < arr.count(); i++)
			{
				if (arr.at(i).toObject()["value"].toString() == value)
				{
					idx = i;
				}
				cmb->addItem(
						arr.at(i).toObject()["display"].toString(),
						arr.at(i).toObject()["value"].toString());
			}
			cmb->setCurrentIndex(idx);
			ui->tableWidget->setCellWidget(i, 1, cmb);
		}
		else if (type == "bool")
		{
			QComboBox *cmb = new QComboBox(ui->tableWidget);
			cmb->addItem("true", 1);
			cmb->addItem("false", 0);
			if (value == "1")
			{
				cmb->setCurrentIndex(0);
			}
			else
			{
				cmb->setCurrentIndex(1);
			}
			ui->tableWidget->setCellWidget(i, 1, cmb);
		}
		else
		{
			twi->setText(value);			
			ui->tableWidget->setItem(i, 1, twi);
		}
	}
}
	
