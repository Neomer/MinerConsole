#ifndef ADMINLISTENER_H
#define ADMINLISTENER_H

#include <QObject>
#include <QTcpServer>

class AdminListener : public QTcpServer
{
	Q_OBJECT
public:
	explicit AdminListener(QObject *parent = 0);
	
signals:
	
public slots:
	
private slots:
	void acceptConnection();
	
};

#endif // ADMINLISTENER_H
