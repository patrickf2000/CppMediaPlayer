#pragma once

#include <QMenu>
#include <QAction>

class VideoPaneMenu : public QMenu {
	Q_OBJECT
public:
	VideoPaneMenu();
	~VideoPaneMenu();
private:
	QAction *open, *play, *pause, *stop;
private slots:
	void onOpenClicked();
	void onPlayClicked();
	void onPauseClicked();
	void onStopClicked();
}; 
