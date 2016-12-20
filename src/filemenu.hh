//filemenu.hh
//The header file for the file menu.
#pragma once

#include <QMenu>
#include <QAction>

class FileMenu : public QMenu {
    Q_OBJECT
public:
    FileMenu();
    ~FileMenu();
    static void refreshRecentEntries();
private:
    QAction *open, *quit;
    static QMenu *recent;
private slots:
	void onOpenClicked();
};
