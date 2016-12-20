#CppMediaPlayer.pro
#The qmake build file for CppMediaPlayer

QT += core gui widgets multimedia multimediawidgets
CONFIG += release c++11

TARGET = cpp-media-player
TEMPLATE = app

DESTDIR = ./build
MOC_DIR = ./build
OBJECTS_DIR = ./build

#TODO: Finish
#INSTALLS += target

RESOURCES =

SOURCES = \
    src/actions.cxx \
    src/control.cxx \
    src/editmenu.cxx \
    src/filemenu.cxx \
    src/helpmenu.cxx \
    src/main.cxx \
    src/recent_action.cxx \
    src/recent.cxx \
    src/seekbar.cxx \
    src/tray.cxx \
    src/videopane.cxx \
    src/videopane_menu.cxx \
    src/viewmenu.cxx \
    src/window.cxx \
    src/playlist/listwidget.cxx \
    src/playlist/playlist.cxx \
    src/playlist/settingswidget.cxx \
    src/settings/dialog.cxx \
    src/settings/get_settings.cxx \
    src/settings/volume.cxx \
    src/settings/volume_dial.cxx

HEADERS = \
    src/actions.hh \
    src/control.hh \
    src/editmenu.hh \
    src/filemenu.hh \
    src/helpmenu.hh \
    src/global.hh \
    src/recent_action.hh \
    src/recent.hh \
    src/seekbar.hh \
    src/tray.hh \
    src/videopane.hh \
    src/videopane_menu.hh \
    src/viewmenu.hh \
    src/window.hh \
    src/playlist/listwidget.hh \
    src/playlist/playlist.hh \
    src/playlist/settings.hh \
    src/playlist/settingswidget.hh \
    src/settings/dialog.hh \
    src/settings/get_settings.hh \
    src/settings/volume.hh \
    src/settings/volume_dial.hh
