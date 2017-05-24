#include "AdminListener.h"

AdminListener::AdminListener(QObject *parent) : 
	QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	
}

void AdminListener::acceptConnection()
{
	this->nextPendingConnection();	
}

