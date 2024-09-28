INCLUDEPATH += ./Interface

XPFDIR = $$absolute_path(..)
XPFDIR_BIN = $$XPFDIR/Bin
XPFDIR_SRC = $$XPFDIR/Source

DESTDIR = $$XPFDIR_BIN
CONFIG(debug, debug|release){
    OBJECTS_DIR = $$XPFDIR/Debug/obj
    MOC_DIR     = $$XPFDIR/Debug/moc
    RCC_DIR     = $$XPFDIR/Debug/rcc
    UI_DIR      = $$XPFDIR/Debug/ui
} else {
    OBJECTS_DIR = $$XPFDIR/Release/obj
    MOC_DIR     = $$XPFDIR/Release/moc
    RCC_DIR     = $$XPFDIR/Release/rcc
    UI_DIR      = $$XPFDIR/Release/ui
}

INCLUDEPATH += $$XPFDIR_SRC/include

