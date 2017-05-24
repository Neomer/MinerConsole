#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "StatusBarTimeDisplay.h"
#include "StatusBarMinerState.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainForm(QWidget *parent = 0);
	~MainForm();
	
private:
	Ui::MainForm *ui;
};

#endif // MAINFORM_H
