# izm.pri

IZMDIR = $${PWD}

INCLUDEPATH += \
    $${IZMDIR}

HEADERS += \
    $${IZMDIR}/*.h

SOURCES += \
    $${IZMDIR}/*.cpp

include(dbg/dbg.pri)
include(literals/literals.pri)
