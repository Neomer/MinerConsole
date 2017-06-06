#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QDir>
#include <QFile>
#include <QDebug>

class Settings : public QObject
{
	Q_OBJECT
	
public:
	explicit Settings(QObject *parent = 0);
	~Settings();
	
	void load();
	bool isLoad() { return _isLoad; }
	
	
	Settings * instance() { return _instance; }
	
private:
	Settings *_instance;
	bool _isLoad;
	QJsonArray _supportedMiners;
	QJsonArray _miners;
};



#endif // SETTINGS_H
