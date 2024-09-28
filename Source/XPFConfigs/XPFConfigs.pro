

QT = core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG += file_copies

XPFConfigs.files = \
    $$XPFDIR_SRC/config/XPF.xml \
    $$XPFDIR_SRC/config/XPFPlugins.xml

XPFConfigs.path = $$XPFDIR_BIN/XPFConfig

COPIES += XPFConfigs

XPFUiConfigs.files = \
    $$XPFDIR_SRC/config/XPFUi/screen0.xml \
    $$XPFDIR_SRC/config/XPFUi/XPFUi.xml

XPFUiConfigs.path = $$XPFDIR_BIN/XPFConfig/XPFUi

COPIES += XPFUiConfigs

CONFIG(debug, debug|release){
    TARGET = XPFConfigsPlugind
} else {
    TARGET = XPFConfigsPlugin
}

DESTDIR = $$DESTDIR/XPFPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    XPFConfigsPlugin.h


SOURCES += \
    XPFConfigsPlugin.cpp


FORMS +=

