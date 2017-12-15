// Copyright 2017 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
