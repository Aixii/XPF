

QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = XPFTrayMenuPlugind
} else {
    TARGET = XPFTrayMenuPlugin
}

DESTDIR = $$DESTDIR/XPFPlugins

INCLUDEPATH += Widgets

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    $$XPFDIR_SRC/include/Define/XPFTrayMenuPluginDef.h \
    $$XPFDIR_SRC/include/Define/XPFDef.h \
    Widgets/TrayIconRClickWgt.h \
    XPFTrayMenuPlugin.h \



SOURCES += \
    Widgets/TrayIconRClickWgt.cpp \
    XPFTrayMenuPlugin.cpp \

FORMS += \
    Widgets/TrayIconRClickWgt.ui
