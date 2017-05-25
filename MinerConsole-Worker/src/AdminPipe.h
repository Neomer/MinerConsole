#ifndef ADMINPIPE_H
#define ADMINPIPE_H

#include <QTcpSocket>
#include <QJsonDocument>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include "Miner.h"

class AdminPipe : public QObject
{
	Q_OBJECT
	
public:
	AdminPipe(QObject *parent);
	
	void setSocket(QTcpSocket *value) 
	{ 
		_socket = value; 
		connect(_socket, SIGNAL(readyRead()), this, SLOT(readData()));
	}
	QTcpSocket *getSocket() const { return _socket; }
	
	void setMiner(Miner *value) { _miner = value; }
	Miner * miner() const { return  _miner; }
	
	
private slots:
	void readData();
	
private:
	QTcpSocket *_socket;
	Miner *_miner;
};

#endif // ADMINPIPE_H
