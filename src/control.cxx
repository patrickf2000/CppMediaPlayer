// Copyright 2018 Patrick Flynn
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
#include <QPixmap>
#include <QVariant>
#include <QWidgetAction>
#include <QMenu>

#include "control.hh"
#include "actions.hh"
#include "videopane.hh"
#include "seekbar.hh"

ControlBar::ControlBar() {
    open = new QToolButton;
    play = new QToolButton;
    pause = new QToolButton;
    stop = new QToolButton;
    back = new QToolButton;
    next = new QToolButton;
    seekbar = new SeekBar;
    volume = new QToolButton;

    volume->setPopupMode(QToolButton::InstantPopup);
    QMenu *menu = new QMenu();
    volume->setMenu(menu);

    volumeSlider = new QSlider;
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(VideoPane::player->volume());
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(onVolumeSliderClicked(int)));

    QWidgetAction *va = new QWidgetAction(menu);
    va->setDefaultWidget(volumeSlider);
    menu->addAction(va);

    QPixmap documentOpenIcon(":/icons/document-open.svg");
    QPixmap playIcon(":/icons/media-playback-start.svg");
    QPixmap pauseIcon(":/icons/media-playback-pause.svg");
    QPixmap stopIcon(":/icons/media-playback-stop.svg");
    QPixmap backIcon(":/icons/media-seek-backward.svg");
    QPixmap nextIcon(":/icons/media-seek-forward.svg");
    QPixmap volumeIcon(":/icons/audio-volume-high.svg");

    open->setIcon(QIcon::fromTheme("document-open",documentOpenIcon));
    play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
    pause->setIcon(QIcon::fromTheme("media-playback-pause",pauseIcon));
    stop->setIcon(QIcon::fromTheme("media-playback-stop",stopIcon));
    back->setIcon(QIcon::fromTheme("media-seek-backward",backIcon));
    next->setIcon(QIcon::fromTheme("media-seek-forward",nextIcon));
    volume->setIcon(QIcon::fromTheme("audio-volume-high",volumeIcon));

    connect(open,&QToolButton::clicked,this,&ControlBar::onOpenClicked);
    connect(play,&QToolButton::clicked,this,&ControlBar::onPlayClicked);
    connect(pause,&QToolButton::clicked,this,&ControlBar::onPauseClicked);
    connect(stop,&QToolButton::clicked,this,&ControlBar::onStopClicked);
    connect(back,&QToolButton::clicked,this,&ControlBar::onBackClicked);
    connect(next,&QToolButton::clicked,this,&ControlBar::onNextClicked);

    this->addWidget(open);
    this->addWidget(play);
    this->addWidget(pause);
    this->addWidget(stop);
    this->addWidget(back);
    this->addWidget(next);
    this->addWidget(seekbar);
    this->addWidget(volume);
}

ControlBar::~ControlBar() {
    delete open;
    delete play;
    delete pause;
    delete stop;
    delete back;
    delete next;
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

void ControlBar::onBackClicked() {
    Actions::seekBack();
}

void ControlBar::onNextClicked() {
    Actions::seekForward();
}

void ControlBar::onVolumeSliderClicked(int val) {
    VideoPane::player->setVolume(val);
}
