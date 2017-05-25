#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include "StatusBarTimeDisplay.h"
#include "StatusBarMinerState.h"
#include "AdminPipe.h"

#include "Miners/ClaymoreEthDualMiner.h"
#include "Miners/MinergateMiner.h"

namespace Ui {
	class MainForm;
}

class MainForm : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainForm(QWidget *parent = 0);
	~MainForm();
	
private slots:
	void writeToConsole(QString text);
	
private:
	void parseEscapeSequence(int attribute, QListIterator< QString > & i, QTextCharFormat & textCharFormat, QTextCharFormat const & defaultTextCharFormat);
	void setTextTermFormatting(QPlainTextEdit * textEdit, QString const & text);
	
	Ui::MainForm *ui;
	MinergateMiner * _miner;
	AdminPipe *_pipe;
};

#endif // MAINFORM_H
