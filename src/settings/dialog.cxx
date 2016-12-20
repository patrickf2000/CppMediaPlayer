//dialog.cxx
//The settings dialog.
#include <QDialog>
#include <QVBoxLayout>

#include "dialog.hh"
#include "volume.hh"

SettingsDialog::SettingsDialog() {
	this->setWindowTitle("Settings");
	this->resize(300,400);
	
	mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);
	
	volume = new Volume;
	
	mainLayout->addWidget(volume,5,Qt::AlignTop);
}

SettingsDialog::~SettingsDialog() {
	delete mainLayout;
	delete volume;
}
