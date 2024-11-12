
PRODIR = $$absolute_path(..)

COMPILER = .
MAKE_TYPE = .

win32 {
    msvc {
        COMPILER = MSVC
    }
    mingw {
        COMPILER = MINGW
    }
}

CONFIG(debug, debug|release){
    OBJECTS_DIR = $$PRODIR/Debug/obj
    MOC_DIR     = $$PRODIR/Debug/moc
    RCC_DIR     = $$PRODIR/Debug/rcc
    UI_DIR      = $$PRODIR/Debug/ui
    MAKE_TYPE   = Debug
} else {
    OBJECTS_DIR = $$PRODIR/Release/obj
    MOC_DIR     = $$PRODIR/Release/moc
    RCC_DIR     = $$PRODIR/Release/rcc
    UI_DIR      = $$PRODIR/Release/ui
    MAKE_TYPE   = Release
}

PRODIR_BIN = $$PRODIR/Bin/$$MAKE_TYPE/$$COMPILER
PRODIR_SRC = $$PWD
PRODIR_INC = $$PRODIR_SRC/Include
PRODIR_LIB = $$PRODIR/Lib

PRODIR_BIN = $$absolute_path($$PRODIR_BIN)

DESTDIR = $$PRODIR_BIN
DESTDIR_LIB = $$PRODIR_LIB


INCLUDEPATH += $$PRODIR_INC

