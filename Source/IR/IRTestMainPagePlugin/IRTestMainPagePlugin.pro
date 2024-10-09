

QT += core gui xml network sql printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (../../XPF.pri)

CONFIG += c++11

TEMPLATE = lib

CONFIG += plugin

CONFIG(debug, debug|release){
    TARGET = IRTestMainPagePlugind
} else {
    TARGET = IRTestMainPagePlugin
}

DESTDIR = $$DESTDIR/IRPlugins

INCLUDEPATH += Widgets
INCLUDEPATH += Defines
INCLUDEPATH += $$XPFDIR_SRC/include/IR

HEADERS += \
    $$XPFDIR_SRC/include/IXPFPlugin.h \
    ../../include/IR/IRMathTool.h \
    Defines/IRTestParamDefine.h \
    IRTestMainDataHandler.h \
    IRTestMainPagePlugin.h \
    Widgets/CRefreshButton.h \
    Widgets/CStatusLabel.h \
    Widgets/IR_ImmediateTestWgt.h \
    Widgets/IR_InstrumentPanel.h \
    Widgets/IR_ParamSettingWgt.h \
    Widgets/IR_TestOperatorWgt.h \
    Widgets/qcatenaryplot.h \
    Widgets/qcustomplot.h \
    Widgets/smoothcurvegenerator.h



SOURCES += \
    IRTestMainDataHandler.cpp \
    IRTestMainPagePlugin.cpp \
    Widgets/CRefreshButton.cpp \
    Widgets/CStatusLabel.cpp \
    Widgets/IR_ImmediateTestWgt.cpp \
    Widgets/IR_InstrumentPanel.cpp \
    Widgets/IR_ParamSettingWgt.cpp \
    Widgets/IR_TestOperatorWgt.cpp \
    Widgets/qcatenaryplot.cpp \
    Widgets/qcustomplot.cpp



FORMS += \
    Widgets/IR_ImmediateTestWgt.ui \
    Widgets/IR_ParamSettingWgt.ui \
    Widgets/IR_TestOperatorWgt.ui

RESOURCES += \
    IRTestMainPageResource.qrc


