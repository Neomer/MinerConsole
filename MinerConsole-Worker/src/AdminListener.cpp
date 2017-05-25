#include "AdminListener.h"

AdminListener::AdminListener(QObject *parent) : 
	QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	connect(this, SIGNAL(acceptError(QAbstractSocket::SocketError)), 
			this, SLOT(acceptError(QAbstractSocket::SocketError)));
	
}

void AdminListener::acceptConnection()
{
	_pipe->setSocket(this->nextPendingConnection());	
}

void AdminListener::acceptError(QAbstractSocket::SocketError err)
{
	switch (err)
	{
		default:
			qDebug("%s", tr("Accept socket error: %1").arg(
					   QString::number((int) err)).toUtf8().constData());
			break;
	}
}

