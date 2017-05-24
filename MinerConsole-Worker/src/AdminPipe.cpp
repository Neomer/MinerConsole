#include "AdminPipe.h"

AdminPipe::AdminPipe(QTcpSocket *socket, QObject *parent) : 
	QObject(parent),
	_socket(socket)
{
	connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void AdminPipe::readData()
{
	_socket->readAll();
}

