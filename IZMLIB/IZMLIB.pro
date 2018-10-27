QT -= gui

TARGET = IZMLIB
TEMPLATE = lib

CONFIG -= lib_bundle
CONFIG += c++14
CONFIG += msvc

msvc: include(msvc.pri)

IZMLIBDIR = $${PWD}

CONFIG(debug, debug|release) {
    DESTDIR = $${IZMLIBDIR}/lib/debug/
} else {
    DESTDIR = $${IZMLIBDIR}/lib/release/
}

include(src/izm.pri)

msvc {
    QMAKE_POST_LINK += $$quote(call makeinclude.bat)
}
