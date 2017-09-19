#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDial>
#include <QLCDNumber>
#include <QPushButton>

#include "volume_dial.hh"
#include "volume.hh"
#include "get_settings.hh"

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
	dial->setValue(Settings::getVolume());
	controlsLayout->addWidget(dial);
	
	lcd = new QLCDNumber;
	lcd->setToolTip("If you do not hit ok, the new volume will not be saved.");
	lcd->display(Settings::getVolume());
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
