

QT += core gui xml network sql serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = IRDevicePortManagerPlugind
} else {
    TARGET = IRDevicePortManagerPlugin
}

DESTDIR = $$DESTDIR/IRPlugins

INCLUDEPATH += $$XPFDIR_SRC/include/IR

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    ../../include/IR/IRTestParamDefine.h \
    IRDevicePortDataHandler.h \
    IRDevicePortManagerPlugin.h \
    TestSerialPortReciver.h \
    TestSerialPortSender.h


SOURCES += \
    IRDevicePortDataHandler.cpp \
    IRDevicePortManagerPlugin.cpp \
    TestSerialPortReciver.cpp \
    TestSerialPortSender.cpp


FORMS += \


