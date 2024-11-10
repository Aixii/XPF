

QT = core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../PRO.pri)
include (../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG += file_copies

#XPFConfigs.files = \
#    $$PRODIR_SRC/config/XPF.xml \
#    $$PRODIR_SRC/config/XPFPlugins.xml

#XPFConfigs.path = $$PRODIR_BIN/XPFConfig

#COPIES += XPFConfigs

#XPFUiConfigs.files = \
#    $$PRODIR_SRC/config/XPFUi/screen0.xml \
#    $$PRODIR_SRC/config/XPFUi/XPFUi.xml

#XPFUiConfigs.path = $$PRODIR_BIN/XPFConfig/XPFUi

#COPIES += XPFUiConfigs

#XPFICON.files = \
#    $$PRODIR_SRC/resource/icon.png

#XPFICON.path = $$PRODIR_BIN/XPFResource

#COPIES += XPFICON

CONFIG(debug, debug|release){
    TARGET = XPFConfigsPlugind
} else {
    TARGET = XPFConfigsPlugin
}

DESTDIR = $$DESTDIR/XPFPlugins

HEADERS += \
    ../Include/XPFConfig/IXPFConfigException.h \
    ../Include/XPFConfig/IXPFConfigService.h \
    ../Include/XPFConfig/IXPFConfigurator.h \
    ../Include/XPFConfig/XPFCoreConfigDef.h \
    ../Include/XPFConfig/XPFLoadPluginsConfigDef.h \
    XPFConfigExceptionImpl.h \
    XPFConfigServiceImpl.h \
    XPFConfigsPlugin.h \
    XPFCoreConfigurator.h

SOURCES += \
    XPFConfigExceptionImpl.cpp \
    XPFConfigServiceImpl.cpp \
    XPFConfigsPlugin.cpp \
    XPFCoreConfigurator.cpp



