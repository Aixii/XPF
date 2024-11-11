TEMPLATE = subdirs

CONFIG = ordered \
    qt

include(XPF.pri)

SUBDIRS += \
    XPFConfigs \
    XPFHelper \
    XPFCore \
    XPFUi \
    XPFTrayMenuPlugin \
    XPFDbServicePlugin \
