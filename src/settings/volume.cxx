//volume.cxx
//The source file for the volume settings controls.
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
