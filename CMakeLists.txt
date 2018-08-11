 cmake_minimum_required(VERSION 3.0.0)
project(CppMediaPlayer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS
	Core
	Widgets
	Gui
	Multimedia
	MultimediaWidgets
)

if (WIN32)
    find_library(libsettings REQUIRED HINTS C:/Unix/bin)
    link_directories(C:/Unix/bin)
    include_directories(C:/Unix/include)
else()
    find_library(settings REQUIRED)
endif()

add_compile_options(-std=c++11)

add_subdirectory(src)

if (UNIX)
	install(FILES share/cpp-media-player.desktop DESTINATION /usr/share/applications)
	install(CODE "execute_process(COMMAND update-desktop-database)")
endif()
