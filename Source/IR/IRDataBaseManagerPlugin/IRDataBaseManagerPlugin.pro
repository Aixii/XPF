

QT += core gui xml network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = IRDataBaseManagerPlugind
} else {
    TARGET = IRDataBaseManagerPlugin
}

LIBS += -L$$XPFDIR_BIN/XPFPlugins -lXPFDbServicePlugind

DESTDIR = $$DESTDIR/IRPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    IRDataBaseManagerPlugin.h \
    UserDbManager.h

SOURCES += \
    IRDataBaseManagerPlugin.cpp \
    UserDbManager.cpp

FORMS += \


