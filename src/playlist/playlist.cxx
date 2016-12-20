//playlist.cxx
#include <QVBoxLayout>

#include "playlist.hh"
#include "listwidget.hh"
#include "settingswidget.hh"

PlayList::PlayList() {
	this->setFixedWidth(200);

	QVBoxLayout *layout = new QVBoxLayout;
	this->setLayout(layout);

	tabs = new QTabWidget;
	layout->addWidget(tabs);
	
	tabs->addTab(new PlayListWidget,"Playlist");
	tabs->addTab(new PlaylistSettingsWidget,"Settings");
}

PlayList::~PlayList() {
} 
