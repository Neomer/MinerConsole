#include <QApplication>
#include <QTextCodec>

#include "MainForm.h"
#include "Settings.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	
	Settings s(&a);
	s.load();
	if (!s.isLoad())
	{
		qDebug() << "Terminate program!";
		return -1;
	}
	
	
	MainForm mf;
	mf.show();
	
	return a.exec();
}
