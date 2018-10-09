// Copyright 2017 Patrick Flynn
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
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QString>
#include <QVector>
#include <QList>

#include "filemenu.hh"
#include "../actions.hh"
#include "recent.hh"
#include "recent_action.hh"

QMenu *FileMenu::recent;

FileMenu::FileMenu() {
	this->setTitle("File");

    open = new QAction("Open",this);
	recent = new QMenu("Recent");
    quit = new QAction("Quit",this);

    QPixmap openIcon(":/icons/document-open.svg");
    QPixmap quitIcon(":/icons/window-close.svg");

    open->setIcon(QIcon::fromTheme("document-open",openIcon));
    quit->setIcon(QIcon::fromTheme("window-close",quitIcon));

    connect(open,&QAction::triggered,this,&FileMenu::onOpenClicked);
    connect(quit,&QAction::triggered,qApp,&QApplication::quit);

    open->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    quit->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Q));
	
	refreshRecentEntries();

	this->addAction(open);
	this->addMenu(recent);
	this->addAction(quit);
}

FileMenu::~FileMenu() {
	delete open;
	delete recent;
	delete quit;
}

void FileMenu::refreshRecentEntries() {
	QList<QAction *> menuActions = recent->actions();
    if (!menuActions.empty()) {
		for (int i = 0; i<menuActions.size(); i++) {
			recent->removeAction(menuActions.at(i));
		}
	}
	Recent *recentItems = new Recent;
	QVector<QString> *items = recentItems->getRecentItems();
	if (items->size()==0) {
		QAction *none = new QAction("None",recent);
		none->setEnabled(false);
		recent->addAction(none);
	} else {
		QVector<QString> *to_add = new QVector<QString>();
		for (int i = 0; i<items->size(); i++) {
			to_add->push_back(items->at(i));
		}
		for (int i = 0; i<to_add->size(); i++) {
			recent->addAction(new RecentAction(to_add->at(i),recent));
		}
	}
}

void FileMenu::onOpenClicked() {
	Actions::open();
}
