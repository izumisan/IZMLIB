# qmvvmlib.pri

INCDIR = $${PWD}/include
LIBDIR = $${PWD}/lib

INCLUDEPATH += $${INCDIR}

CONFIG(debug, debug|release) {
    msvc: LIBS += $$quote($${LIBDIR}/debug/izm.qmvvm.lib)
} else {
    msvc: LIBS += $$quote($${LIBDIR}/release/izm.qmvvm.lib)
}

QML_IMPORT_PATH = $${PWD}/qml
RESOURCES += $${PWD}/qmvvm.qrc