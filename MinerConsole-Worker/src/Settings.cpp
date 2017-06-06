#include "Settings.h"

Settings::Settings(QObject *parent) : 
	QObject(parent),
	_isLoad(false)
{

}

Settings::~Settings()
{
	
}

void Settings::load()
{
	if (!QFile::exists("MinerConsole.Worker.settings"))
	{
		qDebug("%s", "Settings file not found!");
		return;
	}
	
	QFile file("MinerConsole.Worker.settings");
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug("%s", "Settings file not found!");
		return;
	}
	QString sFile = file.readAll();
	QJsonParseError error;
	QJsonDocument json = QJsonDocument::fromJson(sFile.toUtf8(), &error);
	
	if (error.error != error.NoError)
	{
		int offset = error.offset - qMin(error.offset, 10);
		
		qDebug() << "Settings file corrupted! JSON error: " 
				 << error.errorString() 
				 << " in symbol " 
				 << sFile.mid(offset, 30);
		return;
	}
	
/*
	if (json.isEmpty() || json.isNull() || !json.isObject())
	{
		qFatal("%s", "Settings file corrupted!");
		return;
	}
*/	
	_supportedMiners = json.object()["supported_miners"].toArray();
	_miners = json.object()["miners"].toArray();
	
	_isLoad = true;
}

QJsonObject Settings::minerByType(QString type)
{
	if (!isLoad())
		return QJsonObject();		
	
	for (int i = 0; i < Settings::instance().supportedMiners().count(); i++)
	{
		if (Settings::instance().supportedMiners().at(i).toObject()["type"] == type)
		{
			return Settings::instance().supportedMiners().at(i).toObject();
		}
	}
	return QJsonObject();
}

