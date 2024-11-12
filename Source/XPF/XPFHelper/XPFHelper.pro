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

DEFINES += HELPER_EXPORTS

DESTDIR = $$DESTDIR_LIB

HEADERS += \
    ../Include/XPFHelper/IXPFPluginHelper.h \
    Private/MessageSenderPrivate.h \
    Private/XPFPluginHelperImplPrivate.h \
    XPFPluginHelperImpl.h


SOURCES += \
    Private/MessageSenderPrivate.cpp \
    Private/XPFPluginHelperImplPrivate.cpp \
    XPFPluginHelperImpl.cpp

QMAKE_POST_LINK += xcopy /D /F /E /Y \"$${DESTDIR}/$${TARGET}.dll\" \"$${PRODIR_BIN}/\"

