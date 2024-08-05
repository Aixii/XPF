
include (../XPF.pri)

TEMPLATE = app

CONFIG -= qt

CONFIG += c++11

CONFIG(debug, debug|release){
    OBJECTS_DIR = $$XPFDIR/Debug/launcher/obj
    RCC_DIR     = $$XPFDIR/Debug/launcher/rcc
} else {
    OBJECTS_DIR = $$XPFDIR/Release/launcher/obj
    RCC_DIR     = $$XPFDIR/Release/launcher/rcc
}

RCC_DIR     =
UI_DIR      =

TARGET = XPFLauncher

SOURCES += \
        main.cpp


