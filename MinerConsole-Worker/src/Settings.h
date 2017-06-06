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
	
	void load();
	bool isLoad() { return _isLoad; }
	
	static Settings &instance() 
	{
		static Settings s;
        return s;
	}
	
	QJsonArray supportedMiners() const { return _supportedMiners; }
	QJsonArray miners() const { return _miners; }
	
	QJsonObject minerByType(QString type);
	
private:
	explicit Settings(QObject *parent = 0);
	~Settings();
	Settings(Settings const&);
    Settings& operator= (Settings const&);

	
	bool _isLoad;
	QJsonArray _supportedMiners;
	QJsonArray _miners;
};



#endif // SETTINGS_H
