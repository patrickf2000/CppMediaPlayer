//main.cxx
//The main file for odyssey-media-player
#include <QApplication>
#include <QCoreApplication>
#include <QPixmap>
#include <QMediaContent>

#include "window.hh"
#include "videopane.hh"
#include "global.hh"

Vars globalVars;

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);

    QCoreApplication::setOrganizationName("CppMediaPlayer");
    QCoreApplication::setApplicationName("CppMediaPlayer");

    globalVars.window = new Window();
    globalVars.window->showMaximized();

    if (argc>1) {
        QString entry = argv[1];
        VideoPane::player->setMedia(QMediaContent(QUrl::fromLocalFile(entry)));
        VideoPane::startPlaying();
    }

    return app.exec();
}
