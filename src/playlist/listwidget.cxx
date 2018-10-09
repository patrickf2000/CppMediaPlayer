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
#include <QVBoxLayout>
#include <QToolBar>
#include <QIcon>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QPixmap>

#include "listwidget.hh"
#include "../videopane.hh"
#include "settings.hh"

PlayListWidget::PlayListWidget() {
	this->setFrameShape(QFrame::NoFrame);

    openedPlaylist = "untitled";
    originalItems = new QList<QString>();

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0,0,0,0);
	this->setLayout(layout);
	
    //The top toolbar
	QToolBar *toolbar = new QToolBar;
	layout->addWidget(toolbar,0,Qt::AlignTop);
	
	addItem = new QToolButton;
	removeItem = new QToolButton;
	clearItems = new QToolButton;
	play = new QToolButton;

    addItem->setToolTip("Add content to the playlist");
    removeItem->setToolTip("Remove an item from the playlist.");
    clearItems->setToolTip("Clear the playlist.");
    play->setToolTip("Play the items below.");

    QPixmap addItemIcon(":/icons/list-add.svg");
    QPixmap removeItemIcon(":/icons/window-close.svg");
    QPixmap clearItemsIcon(":/icons/edit-clear.svg");
    QPixmap playIcon(":/icons/media-playback-start.svg");
#ifdef NO_THEME_ICONS
    addItem->setIcon(addItemIcon);
    removeItem->setIcon(removeItemIcon);
    clearItems->setIcon(clearItemsIcon);
    play->setIcon(playIcon);
#else
    addItem->setIcon(QIcon::fromTheme("list-add",addItemIcon));
    removeItem->setIcon(QIcon::fromTheme("window-close",removeItemIcon));
    clearItems->setIcon(QIcon::fromTheme("edit-clear",clearItemsIcon));
    play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
#endif
	
	connect(addItem,&QToolButton::clicked,this,&PlayListWidget::onAddItemClicked);
	connect(removeItem,&QToolButton::clicked,this,&PlayListWidget::onRemoveItemClicked);
	connect(clearItems,&QToolButton::clicked,this,&PlayListWidget::onClearItemsClicked);
	connect(play,&QToolButton::clicked,this,&PlayListWidget::onPlayClicked);
	
	toolbar->addWidget(addItem);
	toolbar->addWidget(removeItem);
	toolbar->addWidget(clearItems);
	toolbar->addWidget(play);
	
	playlistItems = new QListWidget;
	layout->addWidget(playlistItems);

    //The toolbar at the bottom
    QToolBar *bottomToolbar = new QToolBar;
    layout->addWidget(bottomToolbar,0,Qt::AlignBottom);

    newList = new QToolButton;
    openList = new QToolButton;
    saveList = new QToolButton;
    saveListAs = new QToolButton;

    newList->setToolTip("Start a new playlist.");
    openList->setToolTip("Open a playlist.");
    saveList->setToolTip("Save the playlist.");
    saveListAs->setToolTip("Save the current playlist as...");

    QPixmap newListIcon(":/icons/document-new.svg");
    QPixmap openListIcon(":/icons/document-open.svg");
    QPixmap saveListIcon(":/icons/document-save.svg");
    QPixmap saveListAsIcon(":/icons/document-save-as.svg");
#ifdef NO_THEME_ICONS
    newList->setIcon(newListIcon);
    openList->setIcon(openListIcon);
    saveList->setIcon(saveListIcon);
    saveListAs->setIcon(saveListAsIcon);
#else
    newList->setIcon(QIcon::fromTheme("document-new",newListIcon));
    openList->setIcon(QIcon::fromTheme("document-open",openListIcon));
    saveList->setIcon(QIcon::fromTheme("document-save",saveListIcon));
    saveListAs->setIcon(QIcon::fromTheme("document-save-as",saveListAsIcon));
#endif

    connect(newList,&QToolButton::clicked,this,&PlayListWidget::onNewListClicked);
    connect(openList,&QToolButton::clicked,this,&PlayListWidget::onOpenListClicked);
    connect(saveList,&QToolButton::clicked,this,&PlayListWidget::onSaveListClicked);
    connect(saveListAs,&QToolButton::clicked,this,&PlayListWidget::onSaveListAsClicked);

    bottomToolbar->addWidget(newList);
    bottomToolbar->addWidget(openList);
    bottomToolbar->addWidget(saveList);
    bottomToolbar->addWidget(saveListAs);
}

PlayListWidget::~PlayListWidget() {
	delete addItem;
	delete removeItem;
	delete clearItems;
	delete play;
    delete newList;
    delete openList;
    delete saveList;
    delete saveListAs;
}

int PlayListWidget::checkSave() {
    QMessageBox msg;
    msg.setText("Your playlist has not been saved.");
    msg.setInformativeText("Do you wish to save it?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::Yes);
    int rel = msg.exec();
    return rel;
}

void PlayListWidget::newPlayList() {
    if (playlistItems->count()==0) {
        openedPlaylist = "untitled";
    } else {
        QList<QString> *currentItems = new QList<QString>();
        for (int i = 0; i<playlistItems->count(); i++) {
            currentItems->push_back(playlistItems->item(i)->text());
        }
        if (currentItems==originalItems) {
            openedPlaylist = "untitled";
        } else {
            switch (checkSave()) {
            case QMessageBox::Yes: {
                if (openedPlaylist=="untitled") {
                    savePlayListAs();
                } else {
                    savePlayList();
                }
            } break;
            case QMessageBox::No: {
                openedPlaylist = "untitled";
            } break;
            }
        }
    }
}

void PlayListWidget::openPlayList() {
    if (playlistItems->count()>0) {
        QList<QString> *currentItems = new QList<QString>();
        for (int i = 0; i<playlistItems->count(); i++) {
            currentItems->push_back(playlistItems->item(i)->text());
        }
        if (currentItems!=originalItems) {
            switch (checkSave()) {
            case QMessageBox::No: {
                return;
            } break;
            }
        }
    }

    QFileDialog dialog;
    dialog.setWindowTitle("Open Playlist");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    int rel = dialog.exec();

    if (rel==QFileDialog::Accepted) {
        openedPlaylist = dialog.selectedFiles().at(0);
        QFile file(openedPlaylist);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream reader(&file);
            while (!reader.atEnd()) {
                playlistItems->addItem(reader.readLine());
            }
        } else {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setText("The selected file could not be opened.");
            msg.exec();
        }
    }
}

void PlayListWidget::savePlayList() {
    if (playlistItems->count()==0) {
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText("You cannot save a blank playlist.");
        msg.exec();
        return;
    }
    if (openedPlaylist=="untitled") {
        savePlayListAs();
    } else {
        QFile file(openedPlaylist);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream writer(&file);
            for (int i = 0; i<playlistItems->count(); i++) {
                writer << playlistItems->item(i)->text() + "\n";
            }
            writer << "\n";
        }
    }
}

void PlayListWidget::savePlayListAs() {
    QFileDialog dialog;
    dialog.setWindowTitle("Save As");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    int rel = dialog.exec();

    if (rel==QFileDialog::Accepted) {
        openedPlaylist = dialog.selectedFiles().at(0);
        savePlayList();
    }
}

void PlayListWidget::onAddItemClicked() {
	QFileDialog chooser;
	chooser.setFileMode(QFileDialog::ExistingFiles);
	chooser.setWindowTitle("Add Item to Playlist");
	if (chooser.exec()) {
		QStringList items = chooser.selectedFiles();
		if (items.size()<0) {
			return;
		}
		for (int i = 0; i<items.size(); i++) {
			QString selected = items.at(i);
			playlistItems->addItem(new QListWidgetItem(selected));
		}
	}
}

void PlayListWidget::onRemoveItemClicked() {
	QListWidgetItem *current = playlistItems->currentItem();
	delete current;
}

void PlayListWidget::onClearItemsClicked() {
	playlistItems->clear();
}

void PlayListWidget::onPlayClicked() {
	QMediaPlaylist *playlist = new QMediaPlaylist;
	for (int i = 0; i<playlistItems->count(); i++) {
		playlist->addMedia(QMediaContent(QUrl::fromLocalFile(playlistItems->item(i)->text())));
	}
	if (playlistSettings.random) {
		playlist->setPlaybackMode(QMediaPlaylist::Random);
	}
	VideoPane::setAndRunPlaylist(playlist);
}

void PlayListWidget::onNewListClicked() {
    newPlayList();
}

void PlayListWidget::onOpenListClicked() {
    openPlayList();
}

void PlayListWidget::onSaveListClicked() {
    savePlayList();
}

void PlayListWidget::onSaveListAsClicked() {
    savePlayListAs();
}
