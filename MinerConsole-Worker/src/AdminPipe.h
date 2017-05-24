#ifndef ADMINPIPE_H
#define ADMINPIPE_H

#include <QTcpSocket>
#include <QJsonDocument>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>

class AdminPipe : public QObject
{
	Q_OBJECT
	
public:
	AdminPipe(QTcpSocket *socket, QObject *parent);
	
private slots:
	void readData();
	
private:
	QTcpSocket *_socket;
};

#endif // ADMINPIPE_H
