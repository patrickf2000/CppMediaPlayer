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
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QSettings>

#include "volume.hh"
#include "volume_dial.hh"
#include "get_settings.hh"

Volume::Volume() {
	layout = new QHBoxLayout;
	this->setLayout(layout);
	
	infoLabel = new QLabel("Choose default volume:");
	layout->addWidget(infoLabel);
	
	spinner = new QSpinBox();
	spinner->setRange(0,100);
	spinner->setCursor(Qt::PointingHandCursor);
	spinner->setValue(Settings::getVolume());
	layout->addWidget(spinner);
	
	useDial = new QPushButton("Use Dial");
	layout->addWidget(useDial);
	
    connect(spinner,SIGNAL(valueChanged(int)),this,SLOT(onValueChanged(int)));
    connect(useDial,&QPushButton::clicked,this,&Volume::onDialClicked);
}

Volume::~Volume() {
	delete layout;
	delete infoLabel;
	delete spinner;
	delete useDial;
}

void Volume::set(int val) {
    QSettings settings;
    settings.setValue("volume",val);
}

void Volume::onValueChanged(int val) {
	set(val);
}

void Volume::onDialClicked() {
	VolumeDial().exec();
	spinner->setValue(Settings::getVolume());
}
