//tray.cxx
//The source file for the system tray icon.
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include "tray.hh"
#include "global.hh"
#include "videopane.hh"
#include "actions.hh"

SysTray::SysTray() {
    this->setIcon(QIcon::fromTheme("applications-multimedia"));

    contextMenu = new QMenu;
    this->setContextMenu(contextMenu);

    play = new QAction(QIcon::fromTheme("media-playback-start"),"Play",contextMenu);
    pause = new QAction(QIcon::fromTheme("media-playback-pause"),"Pause",contextMenu);
    stop = new QAction(QIcon::fromTheme("media-playback-stop"),"Stop",contextMenu);
    open = new QAction(QIcon::fromTheme("document-open"),"Open",contextMenu);
    hideWindow = new QAction("Hide Window",contextMenu);
    quit = new QAction(QIcon::fromTheme("window-close"),"Quit",contextMenu);

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
