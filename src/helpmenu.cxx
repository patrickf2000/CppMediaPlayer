//helpmenu.cxx
//The source file for the help menu.
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QApplication>
#include <QPixmap>

#include "helpmenu.hh"

HelpMenu::HelpMenu() {
    this->setTitle("Help");

    about = new QAction("About",this);
    aboutQt = new QAction("About Qt",this);

    QPixmap aboutIcon(":/icons/help-about.png");
#ifdef NO_THEME_ICONS
    about->setIcon(aboutIcon);
#else
    about->setIcon(QIcon::fromTheme("help-about",aboutIcon));
#endif

    connect(about,SIGNAL(triggered(bool)),this,SLOT(onAboutClicked()));
    connect(aboutQt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));

    this->addAction(about);
    this->addAction(aboutQt);
}

HelpMenu::~HelpMenu() {
    delete about;
    delete aboutQt;
}

void HelpMenu::onAboutClicked() {
    QMessageBox msg;
    msg.setText("CppMediaPlayer\n"
                "A music and video player written in C++ using Qt.\n\n"
                "Written by pdf4664 <pdf4664@outlook.com>");
    msg.exec();
}
