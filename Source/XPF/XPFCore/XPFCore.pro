
QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../PRO.pri)
include(../XPF.pri)

CONFIG += c++11

TARGET = XPF

DESTDIR = $$PRODIR_BIN

msvc {
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8
}

HEADERS += \
    $$XPFDIR_INC/XPFCore/XPFCoreTopicDef.h \
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

