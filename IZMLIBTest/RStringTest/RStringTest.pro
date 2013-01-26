QT       += testlib

QT       -= gui

TARGET = tst_rstringtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += testcase
include(RStringTest.pri)

SOURCES += tst_rstringtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
