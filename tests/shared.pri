# shared.pri

CONFIG += c++14
CONFIG += msvc
msvc: include(msvc.pri)

IZMLIBDIR = $${PWD}/../IZMLIB/
include($${IZMLIBDIR}/src/izm.pri)
