#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>
#include "Settings.h"
#include <QTreeWidgetItem>

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
	Q_OBJECT
	
public:
	explicit SettingsDlg(QWidget *parent = 0);
	~SettingsDlg();

private slots:
	void saveSettings();
    void listIndexChanged(QTreeWidgetItem *item, int column);
	
private:
	Ui::SettingsDlg *ui;
    QTreeWidgetItem *_coins, *_miners;
};

#endif // SETTINGSDLG_H
