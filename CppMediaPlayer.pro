QT = core widgets gui multimedia multimediawidgets
TEMPLATE = app
CONFIG += -std=c++11

MOC_DIR = ./build
OBJECTS_DIR = ./build

include(src/src.pri)