#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T20:52:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_inifilemanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../IZMLIBTest.pri)

SOURCES += tst_inifilemanagertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
