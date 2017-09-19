#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QKeyEvent>

#include "playlist/playlist.hh"
#include "videopane.hh"
#include "control.hh"
#include "seekbar.hh"
#include "tray.hh"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window();
    ~Window();
    void setHeadless(bool headless);
protected:
	void keyPressEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *event);
private:
    QMenuBar *menubar;
    PlayList *playlist;
    VideoPane *videopane;
    ControlBar *controller;
    SeekBar *seek;
    SysTray *systray;
    bool isHeadless;
};
