SOURCES += \
	src/actions.cxx \
	src/control.cxx \
	src/editmenu.cxx \
	src/filemenu.cxx \
	src/helpmenu.cxx \
	src/main.cxx \
	src/recent.cxx \
	src/recent_action.cxx \
	src/seekbar.cxx \
	src/tray.cxx \
	src/videopane.cxx \
	src/videopane_menu.cxx \
	src/viewmenu.cxx \
	src/window.cxx

HEADERS += \
	src/actions.hh \
	src/control.hh \
	src/editmenu.hh \
	src/filemenu.hh \
	src/global.hh \
	src/helpmenu.hh \
	src/recent.hh \
	src/recent_action.hh \
	src/seekbar.hh \
	src/tray.hh \
	src/videopane.hh \
	src/videopane_menu.hh \
	src/viewmenu.hh \
	src/window.hh
	
RESOURCES += \
	src/icons.qrc
	
include(playlist/playlist.pri)
include(settings/settings.pri)