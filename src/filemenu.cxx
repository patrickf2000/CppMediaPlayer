#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QString>
#include <QVector>
#include <QList>

#include "filemenu.hh"
#include "actions.hh"
#include "recent.hh"
#include "recent_action.hh"

QMenu *FileMenu::recent;

FileMenu::FileMenu() {
	this->setTitle("File");

    open = new QAction("Open",this);
	recent = new QMenu("Recent");
    quit = new QAction("Quit",this);

    QPixmap openIcon(":/icons/document-open.png");
    QPixmap quitIcon(":/icons/window-close.png");
#ifdef NO_THEME_ICONS
    open->setIcon(openIcon);
    quit->setIcon(quitIcon);
#else
    open->setIcon(QIcon::fromTheme("document-open",openIcon));
    quit->setIcon(QIcon::fromTheme("window-close",quitIcon));
#endif

	connect(open,SIGNAL(triggered(bool)),this,SLOT(onOpenClicked()));
	connect(quit,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
	
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
	if (not menuActions.empty()) {
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
