#-------------------------------------------------
#
# Project created by QtCreator 2013-01-27T12:10:37
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_utiltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../IZMLIBTest.pri)

SOURCES += tst_utiltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
