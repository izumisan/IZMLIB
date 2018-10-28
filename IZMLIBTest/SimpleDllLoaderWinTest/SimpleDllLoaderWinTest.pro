#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T14:27:42
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_simpledllloaderwintest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../shared.pri)

SOURCES += tst_simpledllloaderwintest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $${PWD}/TestDLL/include/

