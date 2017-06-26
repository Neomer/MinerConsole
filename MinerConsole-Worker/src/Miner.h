#ifndef MINER_H
#define MINER_H

#include <QObject>
#include <QProcess>
#include <QJsonDocument>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "Logs/Logs.h"

class Miner : public QObject
{
	Q_OBJECT
public:
	explicit Miner(QObject *parent = 0);
	~Miner();
	
	bool isRunning();
	
	void setPath(QString value) { _path = value; }
	QString getPath() { return _path; }
	
	void setArguments(QString value) { _arguments = value; }
	QString getArguments() { return _arguments; }
	
	QJsonArray settings() { return _settings; }
	
	virtual QString getMinerName() = 0;
	
	
public slots:
	bool start();
	bool stop();
	
private slots:
	void readStdOut();
	void readStdError();
	void procTerminated();
	
signals:
	void stateChanged(QProcess::ProcessState state);
	void consoleWrite(QString text);
	
private:
	QProcess *_proc;
	QString _path, _arguments;
	QString _minerName;
	bool _needStop;
	QJsonArray _settings;
};

#endif // MINER_H
