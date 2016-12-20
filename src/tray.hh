//tray.hh
//The tray icon for the media player
#pragma once

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class SysTray : public QSystemTrayIcon {
    Q_OBJECT
public:
    SysTray();
    ~SysTray();
private:
    QMenu *contextMenu;
    QAction *play, *pause, *stop, *open, *hideWindow, *quit;
    bool isWindowMaximized;
private slots:
    void onPlayClicked();
    void onPauseClicked();
    void onStopClicked();
    void onOpenClicked();
    void onHideWindowClicked();
};
