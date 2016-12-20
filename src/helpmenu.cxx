//helpmenu.cxx
//The source file for the help menu.
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QApplication>

#include "helpmenu.hh"

HelpMenu::HelpMenu() {
    this->setTitle("Help");

    about = new QAction(QIcon::fromTheme("help-about"),"About",this);
    aboutQt = new QAction("About Qt",this);

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
