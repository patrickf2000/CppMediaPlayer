cmake_minimum_required(VERSION 2.8.12)

project(cpp-media-player)

#set a few much needed variables
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

#Check for needed libraries
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Multimedia MultimediaWidgets)

#We want to use c++11
add_compile_options(-std=c++11)

#Add our source files
set(SRC
	src/actions.cxx
	src/control.cxx
	src/editmenu.cxx
	src/filemenu.cxx
	src/helpmenu.cxx
	src/main.cxx
	src/recent_action.cxx
	src/recent.cxx
	src/seekbar.cxx
	src/tray.cxx
	src/videopane_menu.cxx
	src/videopane.cxx
	src/viewmenu.cxx
	src/window.cxx
)

set(PLAYLIST
	src/playlist/listwidget.cxx
	src/playlist/playlist.cxx
	src/playlist/settingswidget.cxx
)

set(SETTINGS
	src/settings/dialog.cxx
	src/settings/get_settings.cxx
	src/settings/volume_dial.cxx
	src/settings/volume.cxx
)

add_executable(cpp-media-player
	${SRC}
	${PLAYLIST}
	${SETTINGS}
)

#Link to our needed libraries
target_link_libraries(cpp-media-player 
    Qt5::Core
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
)

install(TARGETS cpp-media-player DESTINATION /usr/local/bin)
install(FILES cpp-media-player.desktop DESTINATION /usr/share/applications)
