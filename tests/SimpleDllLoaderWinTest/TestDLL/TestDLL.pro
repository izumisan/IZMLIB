TEMPLATE = lib
CONFIG += dll

TARGET = TestDLL
DLLDESTDIR = $${PWD}/../

DEFINES += EXPORTS

INCLUDEPATH += $${PWD}/include

HEADERS += \
    include/testdll.h

SOURCES += \
    src/testdll.cpp
