

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

CONFIG += file_copies

IRAccoutInterfaces.files = \
    $$XPFDIR_SRC/IR/IRAccountManagerPlugin/IAccountManagerService.h

IRAccoutInterfaces.path = $$XPFDIR_SRC/include/Service/IR

COPIES += IRAccoutInterfaces


DESTDIR = $$DESTDIR/IRPlugins

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    AccountManagerServiceImpl.h \
    IAccountManagerService.h \
    IRAccountDataHandler.h \
    IRAccountManagerPlugin.h \
    Widgets/IR_LoginWgt.h

SOURCES += \
    AccountManagerServiceImpl.cpp \
    IRAccountDataHandler.cpp \
    IRAccountManagerPlugin.cpp \
    Widgets/IR_LoginWgt.cpp

FORMS += \
    Widgets/IR_LoginWgt.ui


