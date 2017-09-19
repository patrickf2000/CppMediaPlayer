#pragma once

#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QSlider>

class ControlBar : public QToolBar {
    Q_OBJECT
public:
    ControlBar();
    ~ControlBar();
private:
    QToolButton *Open, *Play, *Pause, *Stop;
    QLabel *volumeLabel;
    QSlider *volume;
private slots:
    void onOpenClicked();
    void onPlayClicked();
    void onPauseClicked();
    void onStopClicked();
    void onVolumeChanged();
};
