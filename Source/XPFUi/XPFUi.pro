

QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = XPFUiPlugind
} else {
    TARGET = XPFUiPlugin
}

DESTDIR = $$DESTDIR/XPFPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    XPFUiPlugin.h \
    XPFUiTool.h

SOURCES += \
    XPFUiPlugin.cpp \
    XPFUiTool.cpp

FORMS +=
