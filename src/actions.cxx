#include <QString>
#include <QFileDialog>
#include <QStringList>

#include "actions.hh"
#include "videopane.hh"
#include "recent.hh"
#include "filemenu.hh"
#include "global.hh"

bool Actions::maximized;

void Actions::open() {
    QFileDialog dialog;
    dialog.setWindowTitle("Open Media File");
    if (dialog.exec()) {
        QStringList contents = dialog.selectedFiles();
        if (contents.size()<1) {
            return;
        }
        QString selected = contents.at(0);
        Recent recent;
        recent.addRecent(selected);
        recent.write();
        FileMenu::refreshRecentEntries();
        VideoPane::addMedia(selected);
        VideoPane::startPlaying();
    }
}

void Actions::setWindowFullscreen() {
    if (globalVars.window->isFullScreen()) {
        if (maximized) {
            globalVars.window->showMaximized();
        } else {
            globalVars.window->showNormal();
        }
    } else {
        maximized = globalVars.window->isMaximized();
        globalVars.window->showFullScreen();
    }
}
