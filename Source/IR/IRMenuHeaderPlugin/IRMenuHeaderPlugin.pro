

QT += core gui xml network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = IRMenuHeaderPlugind
} else {
    TARGET = IRMenuHeaderPlugin
}

DESTDIR = $$DESTDIR/IRPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    IRMenuHeaderDataHandler.h \
    IRMenuHeaderPlugin.h \
    Widgets/IR_MenuHeaderWgt.h

SOURCES += \
    IRMenuHeaderDataHandler.cpp \
    IRMenuHeaderPlugin.cpp \
    Widgets/IR_MenuHeaderWgt.cpp

FORMS += \
    Widgets/IR_MenuHeaderWgt.ui

RESOURCES += \
    IRMenuHeaderPluginResource.qrc

