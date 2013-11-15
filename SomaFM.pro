TARGET = SomaFM

CONFIG += sailfishapp

SOURCES += \
    src/*.cpp \
    src/XmlItem/*.cpp \
    src/Channel/*.cpp \
    src/Song/*.cpp \
    src/News/*.cpp \
    src/Support/*.cpp

HEADERS += \
    src/*.h \
    src/XmlItem/*.h \
    src/Channel/*.h \
    src/Song/*.h \
    src/News/*.h \
    src/Support/*.h

OTHER_FILES = \
    qml/*.qml \
    qml/cover/*.qml \
    qml/pages/*.qml \
    qml/pages/delegates/*.qml \
    qml/pages/components/*.qml \
    qml/pages/utils/*.qml \
    rpm/$${TARGET}.yaml \
    rpm/$${TARGET}.spec \
    $${TARGET}.desktop

RESOURCES += $${TARGET}.qrc

QT += \
    network\
    sql
