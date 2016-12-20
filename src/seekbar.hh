//seekbar.hh
//Contains the slider that indicates the position of the video.
#pragma once

#include <QToolBar>
#include <QSlider>
#include <QLabel>

class SeekBar : public QToolBar {
    Q_OBJECT
public:
    SeekBar();
    ~SeekBar();
    static void setDuration(qint64 len);
    static void setPosition(qint64 pos);
private:
    static QSlider *seeker;
    static QLabel *timeLabel;
private slots:
    void onSliderMoved(int pos);
};
