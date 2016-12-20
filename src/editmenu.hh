//editmenu.hh
//The header file for the edit menu.
#pragma once

#include <QMenu>
#include <QAction>

class EditMenu : public QMenu {
	Q_OBJECT
public:
	EditMenu();
	~EditMenu();
private:
	QAction *settings;
private slots:
	void onSettingsClicked();
};
