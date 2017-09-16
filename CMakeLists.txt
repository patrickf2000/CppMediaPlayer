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

option(NO_THEME_ICONS "Disable theme icons" OFF)
if (NO_THEME_ICONS)
    message(STATUS "Disabling theme icons")
    add_definitions(-DNO_THEME_ICONS)
else()
    message(STATUS "Building with theme icons")
endif()

add_subdirectory(src)
