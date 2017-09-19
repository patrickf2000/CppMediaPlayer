#include <QMenu>
#include <QAction>
#include <QPixmap>

#include "editmenu.hh"
#include "settings/dialog.hh"

EditMenu::EditMenu() {
	this->setTitle("Edit");
	
    settings = new QAction("Settings",this);

    QPixmap settingsIcon(":/icons/preferences-system.png");
#ifdef NO_THEME_ICONS
    settings->setIcon(settingsIcon);
#else
    settings->setIcon(QIcon::fromTheme("preferences-system",settingsIcon));
#endif
	
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
