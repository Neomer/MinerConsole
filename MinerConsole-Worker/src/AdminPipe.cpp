#include "AdminPipe.h"

AdminPipe::AdminPipe(QObject *parent) : 
	QObject(parent),
	_socket(0),
	_miner(0)
{

}

void AdminPipe::readData()
{
	QString d(_socket->readAll());
	bool isOK = true;

	QJsonDocument json = QJsonDocument::fromJson(d.toUtf8());
	QJsonObject jsonObj = json.object(),
			objResp;
	
	objResp["error"] = false;
	
	float version = jsonObj["version"].toString().toFloat();
	if (version != 1.0)
	{
		objResp["error"] = true;
		objResp["description"] = "Unsupported version! Version 1.0";
		isOK = false;
	}
	if (isOK)
	{
		QString act = jsonObj["action"].toString();
		objResp["action"] = act;
		if (act == "MinerState")
		{
			if (!_miner)
			{
				objResp["error"] = true;
				objResp["description"] = "Miner not set!";
			}
			else
			{
				objResp["result"] = QJsonObject
				{
				      { "state", ((_miner->isRunning()) ? "Work" : "Not running") }
				};
			}
		}
	}
	
	json.setObject(objResp);
	_socket->write(json.toJson());
}

