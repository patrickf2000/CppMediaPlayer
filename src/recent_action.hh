#pragma once

#include <QAction>
#include <QString>
#include <QWidget>

class RecentAction : public QAction {
	Q_OBJECT
public:
	RecentAction(QString text, QWidget *parent);
private slots:
	void onClicked();
};
