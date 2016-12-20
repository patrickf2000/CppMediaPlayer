//volume.hh
//The header file for the default volume settings.
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

class Volume : public QWidget {
	Q_OBJECT
public:
	Volume();
	~Volume();
	static void set(int val);
private:
	QHBoxLayout *layout;
	QLabel *infoLabel;
	QSpinBox *spinner;
	QPushButton *useDial;
private slots:
	void onValueChanged(int val);
	void onDialClicked();
};
