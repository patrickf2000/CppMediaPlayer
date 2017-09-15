cmake_minimum_required(VERSION 3.0.0)
project(CppMediaPlayer)

set(BASE_SRC
	actions.cxx
	control.cxx
	editmenu.cxx
	filemenu.cxx
	helpmenu.cxx
	main.cxx
	recent_action.cxx
	recent.cxx
	seekbar.cxx
	tray.cxx
	videopane_menu.cxx
	videopane.cxx
	viewmenu.cxx
	window.cxx
)

set(PLAYLIST_SRC
	playlist/listwidget.cxx
	playlist/playlist.cxx
	playlist/settingswidget.cxx
)

set(SETTINGS_SRC
	settings/dialog.cxx
	settings/get_settings.cxx
	settings/taskbar_icon.cxx
	settings/volume_dial.cxx
	settings/volume.cxx
)

add_executable(CppMediaPlayer
	${BASE_SRC}
	${PLAYLIST_SRC}
	${SETTINGS_SRC}
)

target_link_libraries(CppMediaPlayer
	Qt5::Core
	Qt5::Widgets
	Qt5::Multimedia
	Qt5::MultimediaWidgets
)
