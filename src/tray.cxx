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
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include "tray.hh"
#include "global.hh"
#include "videopane.hh"
#include "actions.hh"

SysTray::SysTray() {
    QPixmap trayIcon(":/icons/cpp-media-player.png");
#ifdef NO_THEME_ICONS
    this->setIcon(trayIcon);
#else
    this->setIcon(QIcon::fromTheme("applications-multimedia",trayIcon));
#endif

    contextMenu = new QMenu;
    this->setContextMenu(contextMenu);

    play = new QAction("Play",contextMenu);
    pause = new QAction("Pause",contextMenu);
    stop = new QAction("Stop",contextMenu);
    open = new QAction("Open",contextMenu);
    hideWindow = new QAction("Hide Window",contextMenu);
    quit = new QAction("Quit",contextMenu);

    QPixmap documentOpenIcon(":/icons/document-open.png");
    QPixmap playIcon(":/icons/media-playback-start.png");
    QPixmap pauseIcon(":/icons/media-playback-pause.png");
    QPixmap stopIcon(":/icons/media-playback-stop.png");
    QPixmap quitIcon(":/icons/window-close.png");
#ifdef NO_THEME_ICONS
    play->setIcon(playIcon);
    pause->setIcon(pauseIcon);
    stop->setIcon(stopIcon);
    open->setIcon(documentOpenIcon);
    quit->setIcon(quitIcon);
#else
    play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
    pause->setIcon(QIcon::fromTheme("media-playback-pause",pauseIcon));
    stop->setIcon(QIcon::fromTheme("media-playback-stop",stopIcon));
    open->setIcon(QIcon::fromTheme("document-open",documentOpenIcon));
    quit->setIcon(QIcon::fromTheme("window-close",quitIcon));
#endif

    hideWindow->setCheckable(true);

    connect(play,SIGNAL(triggered(bool)),this,SLOT(onPlayClicked()));
    connect(pause,SIGNAL(triggered(bool)),this,SLOT(onPauseClicked()));
    connect(stop,SIGNAL(triggered(bool)),this,SLOT(onStopClicked()));
    connect(open,SIGNAL(triggered(bool)),this,SLOT(onOpenClicked()));
    connect(hideWindow,SIGNAL(triggered(bool)),this,SLOT(onHideWindowClicked()));
    connect(quit,SIGNAL(triggered(bool)),qApp,SLOT(quit()));

    contextMenu->addAction(play);
    contextMenu->addAction(pause);
    contextMenu->addAction(stop);
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
