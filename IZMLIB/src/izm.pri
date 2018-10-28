# izm.pri

IZMDIR = $${PWD}

INCLUDEPATH += \
    $${IZMDIR}

HEADERS += \
    $${IZMDIR}/*.h

SOURCES += \
    $${IZMDIR}/*.cpp

include(literals/literals.pri)
