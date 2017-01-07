//get_settings.cxx
//Gets program settings.
#include <QSettings>

#include "get_settings.hh"

int Settings::getVolume() {
    QSettings settings;
    int vol = settings.value("volume",10).toInt();
    return vol;
}

bool Settings::showTaskbarIcon() {
    QSettings settings;
    bool show = settings.value("taskbar_icon",true).toBool();
    return show;
}
