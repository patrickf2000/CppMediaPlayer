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
#include <QKeyEvent>
#include <QApplication>
#include <QPixmap>
#include <QVariant>
#include <QMenuBar>
#include <cpplib/settings.hh>

#include "window.hh"
#include "videopane.hh"
#include "menubar/filemenu.hh"
#include "menubar/editmenu.hh"
#include "menubar/viewmenu.hh"
#include "menubar/helpmenu.hh"
#include "actions.hh"

using namespace CppLib;

PlayList *Window::playlist;

Window::Window() {
    this->setWindowTitle("Media Player");
    this->resize(900,700);
    this->setAttribute(Qt::WA_QuitOnClose);

    QPixmap winIcon(":/icons/cpp-media-player.svg");
    this->setWindowIcon(QIcon::fromTheme("applications-multimedia",winIcon));

    FileMenu *fileMenu = new FileMenu;
    EditMenu *editMenu = new EditMenu;
    ViewMenu *viewMenu = new ViewMenu;
    HelpMenu *helpMenu = new HelpMenu;

    this->menuBar()->setContextMenuPolicy(Qt::PreventContextMenu);
    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->menuBar()->addMenu(viewMenu);
    this->menuBar()->addMenu(helpMenu);
    
    playlist = new PlayList;
    playlist->hide();
    this->addDockWidget(Qt::LeftDockWidgetArea,playlist);

    QWidget *videopanel = new QWidget;
    videopanel->setStyleSheet("background-color:black;");
    
    QVBoxLayout *videolayout = new QVBoxLayout;
    videopanel->setLayout(videolayout);
    this->setCentralWidget(videopanel);

    videopane = new VideoPane;
    videolayout->addWidget(videopane);

    controller = new ControlBar;
    this->addToolBar(Qt::BottomToolBarArea,controller);

    systray = new SysTray;
    if (QVariant(Settings::getSetting("taskbar/icon","true")).toBool()) {
        systray->show();
    } else {
        systray->hide();
    }
    
    isHeadless = false;
}

void Window::setHeadless(bool headless) {
	if (headless) {
        this->menuBar()->hide();
		playlist->hide();
		controller->hide();
	} else {
        this->menuBar()->show();
		playlist->show();
		controller->show();
	}
}

void Window::dspPlaylist() {
    if (playlist->isVisible()) {
        playlist->hide();
    } else {
        playlist->show();
    }
}

void Window::keyPressEvent(QKeyEvent *event) {
	if ((event->modifiers()==Qt::ControlModifier)and(event->key()==Qt::Key_Q)) {
		qApp->exit();
	} else if ((event->modifiers()==Qt::ControlModifier)and(event->key()==Qt::Key_O)) {
		Actions::open();
	} else if (event->key()==Qt::Key_F11) {
		Actions::setWindowFullscreen();
	} else if ((event->modifiers()==Qt::ControlModifier)and(event->key()==Qt::Key_H)) {
		if (isHeadless) {
			isHeadless = false;
		} else {
			isHeadless = true;
		}
		this->setHeadless(isHeadless);
	}
}

void Window::closeEvent(QCloseEvent *event) {
    delete systray;
    event->accept();
}
