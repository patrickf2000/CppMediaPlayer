//seekbar.cxx
//Contains the seek slider.
#include <QToolBar>
#include <QSlider>
#include <QLabel>

#include "seekbar.hh"
#include "videopane.hh"

QSlider *SeekBar::seeker;
QLabel *SeekBar::timeLabel;

SeekBar::SeekBar() {
    seeker = new QSlider(Qt::Horizontal);
    timeLabel = new QLabel();

    timeLabel->setStyleSheet("color:white;");

    seeker->setMinimum(0);
    seeker->setMaximum(0);

    connect(seeker,SIGNAL(sliderMoved(int)),this,SLOT(onSliderMoved(int)));

    this->addWidget(seeker);
    this->addWidget(timeLabel);
}

SeekBar::~SeekBar() {
    delete seeker;
    delete timeLabel;
}

void SeekBar::setDuration(qint64 len) {
    qint64 seconds = (len/1000);
    qint64 min = (seconds/60);
    qint64 re_sec = (seconds-(min*60));
    seeker->setMinimum(0);
    seeker->setMaximum(len);
    timeLabel->setText(QString::number(min)+":"+QString::number(re_sec));
}

void SeekBar::setPosition(qint64 pos) {
    seeker->setValue(pos);
}

void SeekBar::onSliderMoved(int pos) {
    VideoPane::player->setPosition(pos);
}
