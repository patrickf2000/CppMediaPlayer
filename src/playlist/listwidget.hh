//listwidget.hh
#pragma once

#include <QFrame>
#include <QToolButton>
#include <QListWidget>

class PlayListWidget : public QFrame {
	Q_OBJECT
public:
	PlayListWidget();
	~PlayListWidget();
private:
	QToolButton *addItem, *removeItem, *clearItems, *play;
	QListWidget *playlistItems;
private slots:
	void onAddItemClicked();
	void onRemoveItemClicked();
	void onClearItemsClicked();
	void onPlayClicked();
}; 
