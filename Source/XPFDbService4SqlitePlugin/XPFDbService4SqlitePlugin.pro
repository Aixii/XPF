

QT += core gui xml network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../XPF.pri)

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
    SqlResult.h \
    SqlResultPrivate.h \
    XPFDbService4SqlitePlugin.h \
    XPFDbServiceImpl.h

SOURCES += \
    SqlResult.cpp \
    SqlResultPrivate.cpp \
    XPFDbService4SqlitePlugin.cpp \ \
    XPFDbServiceImpl.cpp

FORMS +=
