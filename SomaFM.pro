# The name of your app
TARGET = SomaFM

# C++ sources
SOURCES += main.cpp \
    src/XmlItem/*.cpp \
    src/Channel/*.cpp \
    src/Song/*.cpp \
    src/News/*.cpp

# C++ headers
HEADERS += src/XmlItem/*.h \
    src/Channel/*.h \
    src/Song/*.h \
    src/News/*.h

# QML files and folders
qml.files = qml main.qml

# The .desktop file
desktop.files = SomaFM.desktop

# Please do not modify the following line.
include(sailfishapplication/sailfishapplication.pri)

OTHER_FILES = \
    rpm/SomaFM.yaml \
    rpm/SomaFM.spec

RESOURCES += SomaFM.qrc

QT += network\
    sql
