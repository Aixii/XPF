QT += core gui xml network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../PRO.pri)
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
    $$XPFDIR_INC/XPFDB/IXPFDbService.h \
    $$XPFDIR_INC/XPFDB/IXPFDbServiceFactory.h \
    $$XPFDIR_INC/XPFDB/IXPFDbSyncService.h \
    $$XPFDIR_INC/XPFDB/ISqlResult.h \
    IXPFDbServiceObj.h \
    SqlResult.h \
    SqlResultPrivate.h \
    XPFDbServiceFacrtoryImpl.h \
    XPFDbServiceImpl.h \
    XPFDbServiceImplPrivate.h \
    XPFDbServiceObject.h \
    XPFDbServicePlugin.h \
    XPFDbServiceWorker.h \
    XPFDbSyncServiceImpl.h

SOURCES += \
    SqlResult.cpp \
    SqlResultPrivate.cpp \
    XPFDbServiceFacrtoryImpl.cpp \
    XPFDbServiceImpl.cpp \
    XPFDbServiceImplPrivate.cpp \
    XPFDbServiceObject.cpp \
    XPFDbServicePlugin.cpp \
    XPFDbServiceWorker.cpp \
    XPFDbSyncServiceImpl.cpp

FORMS +=

