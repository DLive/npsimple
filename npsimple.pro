#-------------------------------------------------
#
# Project created by QtCreator 2011-02-12T11:09:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = npsimple
TEMPLATE = lib

DEFINES += NPSIMPLE_LIBRARY

SOURCES += \
    plugin.cpp \
    npsobjbase.cpp \
    npsobj.cpp \
    npp_gate.cpp \
    npn_gate.cpp \
    np_entry.cpp \
    global.cpp

HEADERS +=\
        npsimple_global.h \
    plugin.h \
    nptypes.h \
    npsobjbase.h \
    npsobj.h \
    npruntime.h \
    npfunctions.h \
    npapi.h \
    mylog.h \
    global.h
