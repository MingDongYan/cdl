#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T13:52:42
#
#-------------------------------------------------

QT       -= gui

TARGET = cdl
TEMPLATE = lib

DEFINES += CDL_LIBRARY

CONFIG += DLL
CONFIG += create_prl


include($$PWD/../CreateRtsPros.pri)


SOURCES += \
    PInPloy.cpp \
    Vec2.cpp \
    CollisionDetection.cpp \
    alt.cpp \
    pdetect.cpp \
    polygonsdis.cpp

HEADERS +=\
        cdl_global.h \
    cdl.hpp \
    Circle.hpp \
    Line.hpp \
    PInPloy.h \
    Polygon.hpp \
    Vec2.hpp \
    CollisionDetection.hpp \
    alt.h \
    pdetect.h \
    cdldebug.h \
    polygonsdis.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=
