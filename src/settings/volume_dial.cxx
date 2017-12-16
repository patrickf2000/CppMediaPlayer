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
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDial>
#include <QLCDNumber>
#include <QPushButton>

#include "volume_dial.hh"
#include "volume.hh"
//#include "get_settings.hh"

VolumeDial::VolumeDial() {
	this->resize(400,200);
	this->setWindowTitle("Set Default Volume");
	
	mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);
	
	controls = new QWidget;
	buttonBox = new QWidget;
	
	controlsLayout = new QHBoxLayout;
	buttonBoxLayout = new QHBoxLayout;
	
	controls->setLayout(controlsLayout);
	buttonBox->setLayout(buttonBoxLayout);
	
	mainLayout->addWidget(controls);
	mainLayout->addWidget(buttonBox);
	
	dial = new QDial;
	dial->setRange(0,100);
    //dial->setValue(Settings::getVolume());
	controlsLayout->addWidget(dial);
	
	lcd = new QLCDNumber;
	lcd->setToolTip("If you do not hit ok, the new volume will not be saved.");
    //lcd->display(Settings::getVolume());
	controlsLayout->addWidget(lcd);
	
	ok = new QPushButton("OK");
	buttonBoxLayout->addWidget(ok,5,Qt::AlignRight);
	
	connect(dial,SIGNAL(valueChanged(int)),this,SLOT(onDialChanged(int)));
	connect(ok,SIGNAL(clicked()),this,SLOT(onOkClicked()));
}

VolumeDial::~VolumeDial() {
	delete controls;
	delete buttonBox;
}

void VolumeDial::onDialChanged(int val) {
	lcd->display(val);
}

void VolumeDial::onOkClicked() {
	Volume::set(dial->value());
	this->done(0);
}
