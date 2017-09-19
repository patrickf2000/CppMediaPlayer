#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDial>
#include <QLCDNumber>
#include <QPushButton>

class VolumeDial : public QDialog {
	Q_OBJECT
public:
	VolumeDial();
	~VolumeDial();
private:
	QVBoxLayout *mainLayout;
	QWidget *controls, *buttonBox;
	QHBoxLayout *controlsLayout, *buttonBoxLayout;
	QDial *dial;
	QLCDNumber *lcd;
	QPushButton *ok;
private slots:
	void onDialChanged(int val);
	void onOkClicked();
};
