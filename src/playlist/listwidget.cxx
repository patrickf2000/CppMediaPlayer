//listwidget.cxx
#include <QVBoxLayout>
#include <QToolBar>
#include <QIcon>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QUrl>

#include "listwidget.hh"
#include "../videopane.hh"
#include "settings.hh"

PlayListWidget::PlayListWidget() {
	this->setFrameShape(QFrame::NoFrame);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0,0,0,0);
	this->setLayout(layout);
	
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
	
	addItem->setIcon(QIcon::fromTheme("list-add"));
	removeItem->setIcon(QIcon::fromTheme("window-close"));
	clearItems->setIcon(QIcon::fromTheme("edit-clear"));
	play->setIcon(QIcon::fromTheme("media-playback-start"));
	
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
}

PlayListWidget::~PlayListWidget() {
	delete addItem;
	delete removeItem;
	delete clearItems;
	delete play;
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
