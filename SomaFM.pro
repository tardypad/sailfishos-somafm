# The name of your app
TARGET = SomaFM

# C++ sources
SOURCES += main.cpp \
    src/*.cpp

# C++ headers
HEADERS += src/*.h

# QML files and folders
qml.files = cover pages main.qml

# The .desktop file
desktop.files = SomaFM.desktop

# Please do not modify the following line.
include(sailfishapplication/sailfishapplication.pri)

OTHER_FILES = \
    rpm/SomaFM.yaml \
    rpm/SomaFM.spec

RESOURCES += SomaFM.qrc

QT += network
