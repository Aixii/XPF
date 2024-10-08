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

CONFIG += file_copies

XPFDbInterfaces.files = \
    $$XPFDIR_SRC/XPFDbServicePlugin/IXPFDbService.h \
    $$XPFDIR_SRC/XPFDbServicePlugin/IXPFDbSyncService.h \
    $$XPFDIR_SRC/XPFDbServicePlugin/IXPFDbServiceFactory.h \
    $$XPFDIR_SRC/XPFDBServicePlugin/SqlResult.h

XPFDbInterfaces.path = $$XPFDIR_SRC/include/Service/XPFDB

COPIES += XPFDbInterfaces

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    IXPFDbService.h \
    IXPFDbServiceFactory.h \
    IXPFDbServiceObj.h \
    IXPFDbSyncService.h \
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

