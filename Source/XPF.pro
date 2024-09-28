include (./XPF.pri)

TEMPLATE = subdirs

SUBDIRS += \
#    XPFLauncher \
    XPFCore \
    XPFUi \
    XPFTrayMenuPlugin \
    XPFLoginPlugin \
#    XPFCreatePluginTool \

QMAKE_POST_LINK += copy config/* ../Bin/XPFConfig





