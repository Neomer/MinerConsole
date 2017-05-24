#include <QApplication>
#include "MainForm.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	
	MainForm mf;
	mf.show();
	
	return a.exec();
}
