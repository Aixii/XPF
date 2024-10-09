

QT += core gui xml network sql serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = IRSettingUiPlugind
} else {
    TARGET = IRSettingUiPlugin
}


DESTDIR = $$DESTDIR/IRPlugins

INCLUDEPATH += Widgets

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    IRSettingDataHandler.h \
    IRSettingUiPlugin.h \
    Widgets/CRefreshButton.h \
    Widgets/IR_ParamValuesSetWgt.h \
    Widgets/IR_SettingDialog.h

SOURCES += \
    IRSettingDataHandler.cpp \
    IRSettingUiPlugin.cpp \
    Widgets/CRefreshButton.cpp \
    Widgets/IR_ParamValuesSetWgt.cpp \
    Widgets/IR_SettingDialog.cpp

FORMS += \
    Widgets/IR_ParamValuesSetWgt.ui \
    Widgets/IR_SettingDialog.ui

RESOURCES += \
    IRSettingUiResource.qrc


