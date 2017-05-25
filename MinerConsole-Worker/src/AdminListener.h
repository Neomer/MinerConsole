#ifndef ADMINLISTENER_H
#define ADMINLISTENER_H

#include <QObject>
#include <QTcpServer>
#include "AdminPipe.h"


class AdminListener : public QTcpServer
{
	Q_OBJECT
public:
	explicit AdminListener(QObject *parent = 0);
	
	void setPipe(AdminPipe *value) { _pipe = value; }
	AdminPipe *getPipe() { return _pipe; }

private slots:
	void acceptConnection();
	void acceptError(QAbstractSocket::SocketError err);
	
private:
	AdminPipe *_pipe; 
};

#endif // ADMINLISTENER_H
