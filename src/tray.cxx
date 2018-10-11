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
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include "tray.hh"
#include "global.hh"
#include "videopane.hh"
#include "actions.hh"

SysTray::SysTray() {
    QPixmap trayIcon(":/icons/cpp-media-player.svg");
    this->setIcon(QIcon::fromTheme("applications-multimedia",trayIcon));

    contextMenu = new QMenu;
    this->setContextMenu(contextMenu);

    play = new QAction("Play",contextMenu);
    pause = new QAction("Pause",contextMenu);
    stop = new QAction("Stop",contextMenu);
    open = new QAction("Open",contextMenu);
    back = new QAction("Back",contextMenu);
    forward = new QAction("Forward",contextMenu);
    hideWindow = new QAction("Hide Window",contextMenu);
    quit = new QAction("Quit",contextMenu);

    QPixmap documentOpenIcon(":/icons/document-open.svg");
    QPixmap playIcon(":/icons/media-playback-start.svg");
    QPixmap pauseIcon(":/icons/media-playback-pause.svg");
    QPixmap stopIcon(":/icons/media-playback-stop.svg");
    QPixmap backIcon(":/icons/media-seek-backward.svg");
    QPixmap forwardIcon(":/icons/media-seek-forward.svg");
    QPixmap quitIcon(":/icons/window-close.svg");

    play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
    pause->setIcon(QIcon::fromTheme("media-playback-pause",pauseIcon));
    stop->setIcon(QIcon::fromTheme("media-playback-stop",stopIcon));
    open->setIcon(QIcon::fromTheme("document-open",documentOpenIcon));
    back->setIcon(QIcon::fromTheme("media-seek-backward",backIcon));
    forward->setIcon(QIcon::fromTheme("media-seek-forward",forwardIcon));
    quit->setIcon(QIcon::fromTheme("window-close",quitIcon));

    hideWindow->setCheckable(true);

    connect(play,&QAction::triggered,this,&SysTray::onPlayClicked);
    connect(pause,&QAction::triggered,this,&SysTray::onPauseClicked);
    connect(stop,&QAction::triggered,this,&SysTray::onStopClicked);
    connect(open,&QAction::triggered,this,&SysTray::onOpenClicked);
    connect(back,&QAction::triggered,this,&SysTray::onBackClicked);
    connect(forward,&QAction::triggered,this,&SysTray::onForwardClicked);
    connect(hideWindow,&QAction::triggered,this,&SysTray::onHideWindowClicked);
    connect(quit,&QAction::triggered,qApp,&QApplication::quit);

    contextMenu->addAction(play);
    contextMenu->addAction(pause);
    contextMenu->addAction(stop);
    contextMenu->addAction(back);
    contextMenu->addAction(forward);
    contextMenu->addAction(open);
    contextMenu->addAction(hideWindow);
    contextMenu->addAction(quit);
}

SysTray::~SysTray() {
    delete contextMenu;
}

void SysTray::onPlayClicked() {
    VideoPane::player->play();
}

void SysTray::onPauseClicked() {
    VideoPane::player->pause();
}

void SysTray::onStopClicked() {
    VideoPane::player->stop();
}

void SysTray::onOpenClicked() {
    bool was = false;
    if (globalVars.window->isHidden()) {
        globalVars.window->show();
        was = true;
    }
    Actions::open();
    if (was) {
        globalVars.window->hide();
    }
}

void SysTray::onBackClicked() {
    Actions::seekBack();
}

void SysTray::onForwardClicked() {
    Actions::seekForward();
}

void SysTray::onHideWindowClicked() {
    if (hideWindow->isChecked()) {
        isWindowMaximized = globalVars.window->isMaximized();
        globalVars.window->hide();
    } else {
        if (isWindowMaximized) {
            globalVars.window->showMaximized();
        } else {
            globalVars.window->show();
        }
    }
}
