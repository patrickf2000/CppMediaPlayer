#include <QAction>
#include <QString>
#include <QWidget>
#include <QMediaContent>
#include <QUrl>

#include "recent_action.hh"
#include "videopane.hh"
#include "recent.hh"
#include "filemenu.hh"

RecentAction::RecentAction(QString text, QWidget *parent) : QAction(parent) {
	this->setText(text);
	connect(this,SIGNAL(triggered(bool)),this,SLOT(onClicked()));
}

void RecentAction::onClicked() {
	Recent recent;
	recent.addRecent(this->text());
	recent.write();
	FileMenu::refreshRecentEntries();
	VideoPane::player->setMedia(QMediaContent(QUrl::fromLocalFile(this->text())));
	VideoPane::player->play();
}
