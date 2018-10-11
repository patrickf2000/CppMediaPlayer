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
#include <QString>
#include <QFileDialog>
#include <QStringList>

#include "actions.hh"
#include "videopane.hh"
#include "menubar/recent.hh"
#include "menubar/filemenu.hh"
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

void Actions::seekBack() {
    int index = VideoPane::player->playlist()->currentIndex();
    VideoPane::player->playlist()->setCurrentIndex(index-1);
}

void Actions::seekForward() {
    int index = VideoPane::player->playlist()->currentIndex();
    VideoPane::player->playlist()->setCurrentIndex(index+1);
}
