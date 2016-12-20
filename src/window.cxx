//window.cxx
//The main window for odyssey-media-player
#include <QKeyEvent>
#include <QApplication>
#include <QSplitter>

#include "window.hh"
#include "videopane.hh"
#include "control.hh"
#include "seekbar.hh"
#include "tray.hh"
#include "filemenu.hh"
#include "editmenu.hh"
#include "viewmenu.hh"
#include "helpmenu.hh"
#include "actions.hh"

Window::Window() {
    this->setWindowTitle("Media Player");
    this->resize(800,700);
    this->setWindowIcon(QIcon::fromTheme("applications-multimedia"));
    this->setAttribute(Qt::WA_QuitOnClose);

    menubar = new QMenuBar;
    this->setMenuBar(menubar);

    menubar->addMenu(new FileMenu);
    menubar->addMenu(new EditMenu);
    menubar->addMenu(new ViewMenu);
    menubar->addMenu(new HelpMenu);
    
    QSplitter *splitter = new QSplitter;
    this->setCentralWidget(splitter);
    
    playlist = new PlayList;
    splitter->addWidget(playlist);

    QWidget *videopanel = new QWidget;
    videopanel->setStyleSheet("background-color:black;");
    
    QVBoxLayout *videolayout = new QVBoxLayout;
    videopanel->setLayout(videolayout);
    splitter->addWidget(videopanel);

    videopane = new VideoPane;
    videolayout->addWidget(videopane);

    seek = new SeekBar;
    videolayout->addWidget(seek);

    controller = new ControlBar;
    this->addToolBar(Qt::BottomToolBarArea,controller);

    systray = new SysTray;
    systray->show();
    
    isHeadless = false;
}

Window::~Window() {
    delete videopane;
    delete controller;
    delete seek;
    delete systray;
}

void Window::setHeadless(bool headless) {
	if (headless) {
		menubar->hide();
		playlist->hide();
		controller->hide();
		seek->hide();
	} else {
		menubar->show();
		playlist->show();
		controller->show();
		seek->show();
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
	qApp->exit();
}
