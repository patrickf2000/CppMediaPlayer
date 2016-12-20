//videopane_menu.cxx
#include "videopane_menu.hh"
#include "actions.hh"
#include "videopane.hh"

VideoPaneMenu::VideoPaneMenu() {
	open = new QAction(QIcon::fromTheme("document-open"),"Open",this);
	play = new QAction(QIcon::fromTheme("media-playback-start"),"Play",this);
	pause = new QAction(QIcon::fromTheme("media-playback-pause"),"Pause",this);
	stop = new QAction(QIcon::fromTheme("media-playback-stop"),"Stop",this);
	
	connect(open,&QAction::triggered,this,&VideoPaneMenu::onOpenClicked);
	connect(play,&QAction::triggered,this,&VideoPaneMenu::onPlayClicked);
	connect(pause,&QAction::triggered,this,&VideoPaneMenu::onPauseClicked);
	connect(stop,&QAction::triggered,this,&VideoPaneMenu::onStopClicked);
	
	this->addAction(open);
	this->addAction(play);
	this->addAction(pause);
	this->addAction(stop);
}

VideoPaneMenu::~VideoPaneMenu() {
	delete open;
	delete play;
	delete pause;
	delete stop;
}

void VideoPaneMenu::onOpenClicked() { Actions::open(); }
void VideoPaneMenu::onPlayClicked() { VideoPane::player->play(); }
void VideoPaneMenu::onPauseClicked() { VideoPane::player->pause(); }
void VideoPaneMenu::onStopClicked() { VideoPane::player->stop(); }
