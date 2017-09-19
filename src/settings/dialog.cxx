#include <QDialog>
#include <QVBoxLayout>

#include "dialog.hh"
#include "volume.hh"
#include "taskbar_icon.hh"

SettingsDialog::SettingsDialog() {
	this->setWindowTitle("Settings");
	this->resize(300,400);
	
	mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

    secondWidget = new QWidget;
    secondLayout = new QVBoxLayout;
    secondWidget->setLayout(secondLayout);
    mainLayout->addWidget(secondWidget,0,Qt::AlignTop);
	
	volume = new Volume;
    tsicon = new TaskbarIcon;
	
    secondLayout->addWidget(volume);
    secondLayout->addWidget(tsicon);
}

SettingsDialog::~SettingsDialog() {
    delete secondLayout;
	delete volume;
    delete tsicon;
}
