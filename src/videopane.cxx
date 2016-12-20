//videopane.cxx
//The source file for the video pane.
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMenu>
#include <QAction>
#include <QMediaContent>
#include <QUrl>

#include "videopane.hh"
#include "seekbar.hh"
#include "settings/get_settings.hh"
#include "videopane_menu.hh"

QMediaPlayer *VideoPane::player;
QMediaPlaylist *VideoPane::playlist;

VideoPane::VideoPane() {
    player = new QMediaPlayer;
    player->setVolume(Settings::getVolume());
    player->setVideoOutput(this);
    player->setPosition(0);
    
	playlist = new QMediaPlaylist;
	player->setPlaylist(playlist);    

    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(onPlayerChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
}

void VideoPane::addMedia(QString path) {
	player->setMedia(QMediaContent(QUrl::fromLocalFile(path)));
}

void VideoPane::setAndRunPlaylist(QMediaPlaylist *playlist) {
	player->setPlaylist(playlist);
	player->play();
}

void VideoPane::startPlaying() {
    player->play();
}

void VideoPane::onPlayerChanged(qint64 pos) {
    SeekBar::setPosition(pos);
}

void VideoPane::onDurationChanged(qint64 pos) {
    SeekBar::setDuration(pos);
}

void VideoPane::mousePressEvent(QMouseEvent *event) {
	if (event->button()==Qt::RightButton) {
		VideoPaneMenu().exec(QCursor::pos());
	}
}
