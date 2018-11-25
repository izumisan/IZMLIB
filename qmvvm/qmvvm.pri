# qmvvm.pri

INCDIR = $${PWD}/include
SRCDIR = $${PWD}/src

INCLUDEPATH += \
    $${INCDIR} \
    $${SRCDIR}

HEADERS += \
    $${INCDIR}/*.h \
    $${SRCDIR}/*.h

SOURCES += \
    $${SRCDIR}/*.cpp
