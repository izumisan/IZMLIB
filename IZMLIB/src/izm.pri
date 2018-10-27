# izm.pri

IZMDIR = $${PWD}

include(literals/literals.pri)

INCLUDEPATH += \
    $${IZMDIR}

HEADERS += \
    $${IZMDIR}/*.h

SOURCES += \
    $${IZMDIR}/*.cpp
