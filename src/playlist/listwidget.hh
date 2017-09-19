#pragma once

#include <QFrame>
#include <QToolButton>
#include <QListWidget>
#include <QString>
#include <QList>

class PlayListWidget : public QFrame {
	Q_OBJECT
public:
	PlayListWidget();
	~PlayListWidget();
private:
	QToolButton *addItem, *removeItem, *clearItems, *play;
	QListWidget *playlistItems;
    QToolButton *newList, *openList, *saveList, *saveListAs;
    QString openedPlaylist;
    QList<QString> *originalItems;
    int checkSave();
    void newPlayList();
    void openPlayList();
    void savePlayList();
    void savePlayListAs();
private slots:
	void onAddItemClicked();
	void onRemoveItemClicked();
	void onClearItemsClicked();
	void onPlayClicked();
    void onNewListClicked();
    void onOpenListClicked();
    void onSaveListClicked();
    void onSaveListAsClicked();
}; 
