//taskbar_icon.cxx
#include <QSettings>
#include <QMessageBox>

#include "taskbar_icon.hh"
#include "get_settings.hh"

TaskbarIcon::TaskbarIcon() {
    layout = new QHBoxLayout;
    this->setLayout(layout);

    showIcon = new QCheckBox("Show taskbar icon:");
    showIcon->setChecked(Settings::showTaskbarIcon());
    layout->addWidget(showIcon);

    connect(showIcon,&QCheckBox::toggled,this,&TaskbarIcon::onShowIconToggled);
}

TaskbarIcon::~TaskbarIcon() {
    delete layout;
    delete showIcon;
}

void TaskbarIcon::onShowIconToggled() {
    QSettings settings;
    if (showIcon->isChecked()) {
        settings.setValue("taskbar_icon",true);
    } else {
        settings.setValue("taskbar_icon",false);
    }
    QMessageBox msg;
    msg.setText("The new settings will take effect on the next program launch.");
    msg.exec();
}
