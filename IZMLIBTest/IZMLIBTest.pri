# IZMLIB�p�e�X�g�v���W�F�N�g�̋���pri�t�@�C��

CONFIG += testcase

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
