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

find_library(settings REQUIRED)

add_compile_options(-std=c++11)

add_subdirectory(src)
