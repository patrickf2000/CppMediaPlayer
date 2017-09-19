#pragma once

#include <QWidget>
#include <QTabWidget>

class PlayList : public QWidget {
	Q_OBJECT
public:
	PlayList();
	~PlayList();
private:
	QTabWidget *tabs;
}; 
