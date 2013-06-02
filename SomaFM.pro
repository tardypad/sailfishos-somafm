# The name of your app
TARGET = SomaFM

# C++ sources
SOURCES += main.cpp

# C++ headers
HEADERS +=

# QML files and folders
qml.files = cover pages main.qml

# The .desktop file
desktop.files = SomaFM.desktop

# Please do not modify the following line.
include(sailfishapplication/sailfishapplication.pri)

OTHER_FILES = rpm/SomaFM.yaml
