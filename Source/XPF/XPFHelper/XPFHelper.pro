QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../PRO.pri)
include(../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG(debug, debug|release){
    TARGET = XPFHelperd
} else {
    TARGET = XPFHelper
}

DEFINES += DLL_EXPORTS

DESTDIR = $$DESTDIR

HEADERS += \
    ../Include/XPFHelper/IXPFPluginHelper.h \
    Private/MessageSenderPrivate.h \
    Private/XPFPluginHelperImplPrivate.h \
    XPFPluginHelperImpl.h


SOURCES += \
    Private/MessageSenderPrivate.cpp \
    Private/XPFPluginHelperImplPrivate.cpp \
    XPFPluginHelperImpl.cpp

