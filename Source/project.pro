
TEMPLATE = subdirs

include(PRO.pri)

CONFIG = ordered \
    qt

SUBDIRS += \
    XPF \
    Plugins

BEFORE_LINK_CMD_LINE = echo Hello world!
    !build_pass:system(xcopy /D /F /E /Y \"$${PWD}/Config/XPF.xml\" \"$${PRODIR_BIN}/XPFConfig/XPF.xml\")
win32 {
}


DISTFILES += \
    $$PRODIR_SRC/Config/XPF.xml \
    $$PRODIR_SRC/Config/XPFPlugins.xml \
    $$PRODIR_SRC/Config/XPFUi/screen0.xml



