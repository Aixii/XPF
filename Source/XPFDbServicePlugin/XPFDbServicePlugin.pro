QT += core gui xml network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = XPFDbServicePlugind
} else {
    TARGET = XPFDbServicePlugin
}

DESTDIR = $$DESTDIR/XPFPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    IXPFDbService.h \
    IXPFDbServiceFactory.h \
    SqlResult.h \
    SqlResultPrivate.h \
    XPFDbServiceFacrtory.h \
    XPFDbServiceImplPrivate.h \
    XPFDbServicePlugin.h \
    XPFDbServiceImpl.h

SOURCES += \
    SqlResult.cpp \
    SqlResultPrivate.cpp \
    XPFDbServiceFacrtory.cpp \
    XPFDbServiceImplPrivate.cpp \
    XPFDbServicePlugin.cpp \ \
    XPFDbServiceImpl.cpp

FORMS +=

