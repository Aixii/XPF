
include (../XPF.pri)

QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# 拷贝命令
win32:QMAKE_COPY = copy
unix:QMAKE_COPY = cp


HEADERS += \
    $$XPFDIR_SRC/interface/IXPFPlugin.h \
    XPFUiPluin.h

SOURCES += \
    XPFUiPluin.cpp
