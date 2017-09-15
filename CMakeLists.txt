cmake_minimum_required(VERSION 3.0.0)
project(CppMediaPlayer)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS
	Core
	Widgets
	Multimedia
	MultimediaWidgets
)

add_compile_options(-std=c++11)

add_subdirectory(src)
