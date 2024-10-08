

QT += core gui xml network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = IRAccountManagerPlugind
} else {
    TARGET = IRAccountManagerPlugin
}

DESTDIR = $$DESTDIR/IRPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    DataHandler.h \
    IRAccountManagerPlugin.h \
    Widgets/IR_LoginWgt.h

SOURCES += \
    DataHandler.cpp \
    IRAccountManagerPlugin.cpp \
    Widgets/IR_LoginWgt.cpp

FORMS += \
    Widgets/IR_LoginWgt.ui

