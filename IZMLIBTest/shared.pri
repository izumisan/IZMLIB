# shared.pri

IZMLIBDIR = $${PWD}/../IZMLIB/

CONFIG += msvc
msvc: include(msvc.pri)

include($${IZMLIBDIR}/src/izm.pri)
