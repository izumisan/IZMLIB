QT       += testlib

QT       -= gui

TARGET = tst_rstringtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../IZMLIBTest.pri)

SOURCES += tst_rstringtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
