include (../XPF.pri)

QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = XPF

DESTDIR = $$XPFDIR_BIN

HEADERS += \
    Private/MessageSenderPrivate.h \
    Private/XPFPluginHelperImplPrivate.h \
    XPFCore.h \
    XPFPluginHelperImpl.h \
    ../include/XPFDef.h


SOURCES += main.cpp \
    Private/MessageSenderPrivate.cpp \
    Private/XPFPluginHelperImplPrivate.cpp \
    XPFCore.cpp \
    XPFGlobal.cpp \
    XPFPluginHelperImpl.cpp \

DISTFILES += \
    ../config/XPF.xml \
    ../config/XPFPlugins.xml

