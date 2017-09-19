#include <QKeyEvent>
#include <QApplication>
#include <QSplitter>
#include <QPixmap>

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
#include "settings/get_settings.hh"

Window::Window() {
    this->setWindowTitle("Media Player");
    this->resize(800,700);
    this->setAttribute(Qt::WA_QuitOnClose);

    QPixmap winIcon(":/icons/cpp-media-player.png");
#ifdef NO_THEME_ICONS
    this->setWindowIcon(winIcon);
#else
    this->setWindowIcon(QIcon::fromTheme("applications-multimedia",winIcon));
#endif

    FileMenu *fileMenu = new FileMenu;
    EditMenu *editMenu = new EditMenu;
    ViewMenu *viewMenu = new ViewMenu;
    HelpMenu *helpMenu = new HelpMenu;

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->menuBar()->addMenu(viewMenu);
    this->menuBar()->addMenu(helpMenu);
    
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

    if (Settings::showTaskbarIcon()) {
        systray = new SysTray;
        systray->show();
    }
    
    isHeadless = false;
}

Window::~Window() {
    delete videopane;
    delete controller;
    delete seek;
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
    delete systray;
    event->accept();
}
