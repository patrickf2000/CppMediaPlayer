//helpmenu.hh
//The help menu for odyssey-media-player
#pragma once

#include <QMenu>
#include <QAction>

class HelpMenu : public QMenu {
    Q_OBJECT
public:
    HelpMenu();
    ~HelpMenu();
private:
    QAction *about, *aboutQt;
private slots:
    void onAboutClicked();
};
