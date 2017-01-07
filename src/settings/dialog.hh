//dialog.hh
//The header file for the dialog window containing the program settings.
#pragma once

#include <QDialog>
#include <QVBoxLayout>

#include "volume.hh"
#include "taskbar_icon.hh"

class SettingsDialog : public QDialog {
	Q_OBJECT
public:
	SettingsDialog();
	~SettingsDialog();
private:
	QVBoxLayout *mainLayout;
    QWidget *secondWidget;
    QVBoxLayout *secondLayout;
	Volume *volume;
    TaskbarIcon *tsicon;
};
