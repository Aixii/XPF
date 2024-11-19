
QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../PRO.pri)
include(../XPF.pri)

CONFIG += c++11

TARGET = XPF

# DEFINES += OUT_ERR

DESTDIR = $$PRODIR_BIN

msvc {
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8
}

CONFIG(debug, debug|release){
    TARGET = XPFd
    LIBS += -L$$PRODIR_LIB -lXPFHelperd
} else {
    TARGET = XPF
    LIBS += -L$$PRODIR_LIB -lXPFHelper
}

HEADERS += \
    $$XPFDIR_INC/XPFCore/XPFCoreTopicDef.h \
    $$XPFDIR_INC/XPFCore/XPFGlobal.h \
    $$XPFDIR_INC/XPFComm/IXPFErrorException.h \
    XPFCore.h \



SOURCES += main.cpp \
    XPFCore.cpp \
    XPFGlobal.cpp \

QMAKE_POST_LINK += $$WINDEPLOY --dir \"$${PRODIR_BIN}\" --libdir \"$${PRODIR_BIN}\" \"$${DESTDIR}/$${TARGET}.exe\"



