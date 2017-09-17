//viewmenu.cxx
//The viewmenu.
#include <QMenu>
#include <QAction>
#include <QPixmap>

#include "viewmenu.hh"
#include "actions.hh"

ViewMenu::ViewMenu() {
    this->setTitle("View");

    fullScreen = new QAction("Fullscreen",this);

    QPixmap fullScreenIcon(":/icons/view-fullscreen.png");
#ifdef NO_THEME_ICONS
    fullScreen->setIcon(fullScreenIcon);
#else
    fullScreen->setIcon(QIcon::fromTheme("view-fullscreen",fullScreenIcon));
#endif

    connect(fullScreen,SIGNAL(triggered(bool)),this,SLOT(onFullScreenClicked()));

    this->addAction(fullScreen);
}

ViewMenu::~ViewMenu() {
    delete fullScreen;
}

void ViewMenu::onFullScreenClicked() {
	Actions::setWindowFullscreen();
}
