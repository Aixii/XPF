
QT = core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../PRO.pri)
include (../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

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



