
TEMPLATE = subdirs

include(PRO.pri)

CONFIG = ordered \
    qt

SUBDIRS += \
    XPF \
    Plugins

DISTFILES += \
    $$PRODIR_SRC/Config/XPF.xml \
    $$PRODIR_SRC/Config/XPFPlugins.xml \
    $$PRODIR_SRC/Config/XPFUi/screen0.xml



