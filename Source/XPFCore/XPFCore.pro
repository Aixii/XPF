
QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../XPF.pri)

CONFIG += c++11

TARGET = XPF

DESTDIR = $$XPFDIR_BIN

HEADERS += \
    $$XPFDIR_SRC/include/Define/XPFCoreDef.h \
    Private/MessageSenderPrivate.h \
    Private/XPFPluginHelperImplPrivate.h \
    XPFCore.h \
    XPFPluginHelperImpl.h \


SOURCES += main.cpp \
    Private/MessageSenderPrivate.cpp \
    Private/XPFPluginHelperImplPrivate.cpp \
    XPFCore.cpp \
    XPFGlobal.cpp \
    XPFPluginHelperImpl.cpp \

