cmake_minimum_required(VERSION 3.0.0)
project(CppMediaPlayer)

set(BASE_SRC
	actions.cxx
	control.cxx
	main.cxx
	seekbar.cxx
	tray.cxx
	videopane.cxx
	videopane_menu.cxx
	window.cxx
	icons.qrc
	rsc.qrc
)

set(MENUBAR_SRC
	menubar/editmenu.cxx
	menubar/filemenu.cxx
	menubar/helpmenu.cxx
	menubar/recent.cxx
	menubar/recent_action.cxx
	menubar/viewmenu.cxx
)

set(PLAYLIST_SRC
	playlist/listwidget.cxx
	playlist/playlist.cxx
	playlist/settingswidget.cxx
)

set(SETTINGS_SRC
	settings/settings_dialog.cxx
	settings/settings_dialog.ui
)

set(SRC
	${BASE_SRC}
	${MENUBAR_SRC}
	${PLAYLIST_SRC}
	${SETTINGS_SRC}
)

add_executable(CppMediaPlayer ${SRC})

target_link_libraries(CppMediaPlayer
	Qt5::Core
	Qt5::Widgets
	Qt5::Gui
	Qt5::Multimedia
	Qt5::MultimediaWidgets
	settings
) 
