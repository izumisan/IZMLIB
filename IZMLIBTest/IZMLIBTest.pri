# IZMLIB用テストプロジェクトの共通priファイル

CONFIG += msvc
msvc: include(msvc.pri)

IZMLIB_TOP = $${PWD}/../IZMLIB/
IZMLIB_INC = $${IZMLIB_TOP}/include/
IZMLIB_SRC = $${IZMLIB_TOP}/src/

INCLUDEPATH += \
    $${IZMLIB_INC}

HEADERS += \
    $${IZMLIB_INC}/*.h \
    $${IZMLIB_SRC}/*.h

SOURCES += \
    $${IZMLIB_SRC}/*.cpp
