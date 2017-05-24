#ifndef MINER_H
#define MINER_H

#include <QObject>
#include <QProcess>

class Miner : public QObject
{
	Q_OBJECT
public:
	explicit Miner(QObject *parent = 0);
	
	bool isRunning();
	
	void setPath(QString value) { _path = value; }
	QString getPath() { return _path; }
	
	void setArguments(QString value) { _arguments = value; }
	QString getArguments() { return _arguments; }
	
	void setMinerName(QString value) { _minerName = value; }
	QString getMinerName() { return _minerName; }
	
public slots:
	bool start();
	bool stop();
	
signals:
	void stateChanged(QProcess::ProcessState state);
	
private:
	QProcess *_proc;
	QString _path, _arguments;
	QString _minerName;
};

#endif // MINER_H
