//videopane_menu.cxx
#include <QPixmap>

#include "videopane_menu.hh"
#include "actions.hh"
#include "videopane.hh"

VideoPaneMenu::VideoPaneMenu() {
    open = new QAction("Open",this);
    play = new QAction("Play",this);
    pause = new QAction("Pause",this);
    stop = new QAction("Stop",this);

    QPixmap documentOpenIcon(":/icons/document-open.png");
    QPixmap playIcon(":/icons/media-playback-start.png");
    QPixmap pauseIcon(":/icons/media-playback-pause.png");
    QPixmap stopIcon(":/icons/media-playback-stop.png");
#ifdef NO_THEME_ICONS
    open->setIcon(documentOpenIcon);
    play->setIcon(playIcon);
    pause->setIcon(pauseIcon);
    stop->setIcon(stopIcon);
#else
    open->setIcon(QIcon::fromTheme("document-open",documentOpenIcon));
    play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
    pause->setIcon(QIcon::fromTheme("media-playback-pause",pauseIcon));
    stop->setIcon(QIcon::fromTheme("media-playback-stop",stopIcon));
#endif
	
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
