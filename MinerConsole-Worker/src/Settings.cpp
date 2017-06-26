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
    LOG_TRACE;

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
	file.close();
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
	
    QJsonArray coins = json.object()["coins"].toArray();
    for (int i = 0; i < coins.count(); i++)
    {
        _coins.append(new Coin(coins.at(i).toObject(), this));
    }

	_isLoad = true;
}

void Settings::setMinerSettings(QString name, QJsonObject &object)
{
    LOG_TRACE << name;

    for (int i = 0; i < miners().count(); i++)
	{
		if (miners().at(i).toObject()["name"] == name)
		{
            _miners.takeAt(i).toObject();
            _miners << object;
		}
	}
}

QJsonObject Settings::supportedMinerByType(QString type)
{
    LOG_TRACE << type;

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

QJsonObject Settings::minerByName(QString name)
{
    LOG_TRACE << name;

    if (!isLoad())
		return QJsonObject();		
	
	for (int i = 0; i < Settings::instance().miners().count(); i++)
	{
		if (Settings::instance().miners().at(i).toObject()["name"] == name)
		{
			return Settings::instance().miners().at(i).toObject();
		}
	}
    return QJsonObject();
}

QList<Coin *> Settings::coinList()
{
    return _coins;
}

void Settings::save()
{
    LOG_TRACE;

    QJsonObject obj;
	obj["miners"] = miners();
	obj["supported_miners"] = supportedMiners();
	QJsonDocument json(obj);
	
	if (!QFile::exists("MinerConsole.Worker.settings"))
	{
		qDebug("%s", "Settings file not found!");
		return;
	}
	
	QFile file("MinerConsole.Worker.settings");
	if (!file.open(QIODevice::WriteOnly))
	{
		qDebug("%s", "Settings file not found!");
		return;
	}

	file.write(json.toJson());
	file.close();
}

