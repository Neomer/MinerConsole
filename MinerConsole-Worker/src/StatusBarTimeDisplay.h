#ifndef STATUSBARTIMEDISPLAY_H
#define STATUSBARTIMEDISPLAY_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
	class StatusBarTimeDisplay;
}

class StatusBarTimeDisplay : public QWidget
{
	Q_OBJECT
	
public:
	explicit StatusBarTimeDisplay(QWidget *parent = 0);
	~StatusBarTimeDisplay();
	
private slots:
	void updateTime();
	
private:
	Ui::StatusBarTimeDisplay *ui;
	QTimer *_tmr;
};

#endif // STATUSBARTIMEDISPLAY_H
