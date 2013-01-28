QT       += testlib

QT       -= gui

TARGET = tst_rstringtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../IZMLIBTest.pri)
include(RStringTest.pri)

SOURCES += tst_rstringtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
