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
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QSlider>
#include <QPixmap>

#include "control.hh"
#include "actions.hh"
#include "videopane.hh"
#include "settings/get_settings.hh"

ControlBar::ControlBar() {
    Open = new QToolButton;
    Play = new QToolButton;
    Pause = new QToolButton;
    Stop = new QToolButton;
    volumeLabel = new QLabel("Volume:");
    volume = new QSlider(Qt::Horizontal);

    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(Settings::getVolume());

    QPixmap documentOpenIcon(":/icons/document-open.png");
    QPixmap playIcon(":/icons/media-playback-start.png");
    QPixmap pauseIcon(":/icons/media-playback-pause.png");
    QPixmap stopIcon(":/icons/media-playback-stop.png");
#ifdef NO_THEME_ICONS
    Open->setIcon(documentOpenIcon);
    Play->setIcon(playIcon);
    Pause->setIcon(pauseIcon);
    Stop->setIcon(stopIcon);
#else
    Open->setIcon(QIcon::fromTheme("document-open",documentOpenIcon));
    Play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
    Pause->setIcon(QIcon::fromTheme("media-playback-pause",pauseIcon));
    Stop->setIcon(QIcon::fromTheme("media-playback-stop",stopIcon));
#endif

    connect(Open,SIGNAL(clicked(bool)),this,SLOT(onOpenClicked()));
    connect(Play,SIGNAL(clicked(bool)),this,SLOT(onPlayClicked()));
    connect(Pause,SIGNAL(clicked(bool)),this,SLOT(onPauseClicked()));
    connect(Stop,SIGNAL(clicked(bool)),this,SLOT(onStopClicked()));
    connect(volume,SIGNAL(valueChanged(int)),this,SLOT(onVolumeChanged()));

    this->addWidget(Open);
    this->addWidget(Play);
    this->addWidget(Pause);
    this->addWidget(Stop);
    this->addWidget(volumeLabel);
    this->addWidget(volume);
}

ControlBar::~ControlBar() {
    delete Open;
    delete Play;
    delete Pause;
    delete Stop;
    delete volumeLabel;
    delete volume;
}

void ControlBar::onOpenClicked() {
    Actions::open();
}

void ControlBar::onPlayClicked() {
    VideoPane::player->play();
}

void ControlBar::onPauseClicked() {
    VideoPane::player->pause();
}

void ControlBar::onStopClicked() {
    VideoPane::player->stop();
}

void ControlBar::onVolumeChanged() {
    VideoPane::player->setVolume(volume->value());
}
