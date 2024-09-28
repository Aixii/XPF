
include (../XPF.pri)

QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = XPFLoginPlugind
} else {
    TARGET = XPFLoginPlugin
}

DESTDIR = $$DESTDIR/XPFPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    XPFLoginPlugin.h \

SOURCES += \
    XPFLoginPlugin.cpp \

FORMS +=

