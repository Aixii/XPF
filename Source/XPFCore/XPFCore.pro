include (../XPF.pri)

QT += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = XPF

#win32:  TARGET_EXT = .exe
#unix:   TARGET_EXT =

## 将可执行文件拷贝到目标路径
#win32 {
#    EXE_PATH = $$replace(XPFDIR_BIN, /, \\)
#    DESTFILE_PATH = $$replace(DESTDIR, /, \\)
#    QMAKE_POST_LINK += $$QMAKE_COPY \"$$DESTFILE_PATH\\$$TARGET$$TARGET_EXT\"  \"$$EXE_PATH\"
#}

HEADERS += \
    Private/MessageSenderPrivate.h \
    Private/XPFPluginHelperImplPrivate.h \
    XPFCore.h \
    XPFPluginHelperImpl.h \
    ../include/XPFDef.h


SOURCES += main.cpp \
    Private/MessageSenderPrivate.cpp \
    Private/XPFPluginHelperImplPrivate.cpp \
    XPFCore.cpp \
    XPFGlobal.cpp \
    XPFPluginHelperImpl.cpp \

