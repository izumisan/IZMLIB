# shared.pri

CONFIG += c++14

win32-msvc {
    include(msvc.pri)
}

IZMLIBDIR = $${PWD}/../IZMLIB/
include($${IZMLIBDIR}/src/izm.pri)
