// Copyright 2017 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMenu>
#include <QAction>
#include <QMediaContent>
#include <QUrl>
#include <QVariant>
#include <cpplib/settings.hh>

#include "videopane.hh"
#include "seekbar.hh"
#include "videopane_menu.hh"

using namespace CppLib;

QMediaPlayer *VideoPane::player;
QMediaPlaylist *VideoPane::playlist;

VideoPane::VideoPane() {
    player = new QMediaPlayer;
    player->setVolume(QVariant(Settings::getSetting("volume","10")).toInt());
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
