//editmenu.cxx
//The source file for the program's edit menu.
#include <QMenu>
#include <QAction>

#include "editmenu.hh"
#include "settings/dialog.hh"

EditMenu::EditMenu() {
	this->setTitle("Edit");
	
	settings = new QAction(QIcon::fromTheme("preferences-system"),"Settings",this);
	
	connect(settings,SIGNAL(triggered(bool)),this,SLOT(onSettingsClicked()));
	
	this->addAction(settings);
}

EditMenu::~EditMenu() {
	delete settings;
}

void EditMenu::onSettingsClicked() {
	SettingsDialog diag;
	diag.exec();
}
