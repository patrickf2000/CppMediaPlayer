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
#include <QPixmap>

#include "videopane_menu.hh"
#include "actions.hh"
#include "videopane.hh"

VideoPaneMenu::VideoPaneMenu() {
    open = new QAction("Open",this);
    play = new QAction("Play",this);
    pause = new QAction("Pause",this);
    stop = new QAction("Stop",this);

    QPixmap documentOpenIcon(":/icons/document-open.svg");
    QPixmap playIcon(":/icons/media-playback-start.svg");
    QPixmap pauseIcon(":/icons/media-playback-pause.svg");
    QPixmap stopIcon(":/icons/media-playback-stop.svg");
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
