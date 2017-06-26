#include <QApplication>
#include <QTextCodec>

#include "Logs/Logs.h"
#include "MainForm.h"
#include "Settings.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

    LOG_TRACE << argc << argv;
	
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	
	Settings::instance().load();
	if (!Settings::instance().isLoad())
	{
		qDebug() << "Terminate program!";
		return -1;
	}
	
	MainForm mf;
	mf.show();
	
	return a.exec();
}
