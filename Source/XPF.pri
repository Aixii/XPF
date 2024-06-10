INCLUDEPATH += ./Interface

XPFDIR = $$absolute_path(..)
XPFDIR_BIN = $$XPFDIR/Bin
XPFDIR_SRC = $$XPFDIR/Source

CONFIG(debug, debug|release){
    DESTDIR = $$XPFDIR/Debug
}else{
    DESTDIR = $$XPFDIR/Release
}

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR     = $$DESTDIR/moc
RCC_DIR     = $$DESTDIR/rcc
UI_DIR      = $$DESTDIR/ui

INCLUDEPATH += $$XPFDIR_SRC/interface
INCLUDEPATH += $$XPFDIR_SRC/include
