//viewmenu.cxx
//The viewmenu.
#include <QMenu>
#include <QAction>

#include "viewmenu.hh"
#include "actions.hh"

ViewMenu::ViewMenu() {
    this->setTitle("View");

    fullScreen = new QAction(QIcon::fromTheme("view-fullscreen"),"Fullscreen",this);

    connect(fullScreen,SIGNAL(triggered(bool)),this,SLOT(onFullScreenClicked()));

    this->addAction(fullScreen);
}

ViewMenu::~ViewMenu() {
    delete fullScreen;
}

void ViewMenu::onFullScreenClicked() {
	Actions::setWindowFullscreen();
}
