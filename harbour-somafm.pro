TARGET = harbour-somafm

VERSION = 2.0.0

CONFIG += sailfishapp

SOURCES += \
    $$files(src/*.cpp) \
    $$files(src/XmlItem/*.cpp) \
    $$files(src/Channel/*.cpp) \
    $$files(src/Song/*.cpp) \
    $$files(src/News/*.cpp) \
    $$files(src/Refresh/*.cpp)

HEADERS += \
    $$files(src/*.h) \
    $$files(src/XmlItem/*.h) \
    $$files(src/Channel/*.h) \
    $$files(src/Song/*.h) \
    $$files(src/News/*.h) \
    $$files(src/Refresh/*.h)

OTHER_FILES = \
    $$files(qml/*.qml) \
    $$files(qml/cover/*.qml) \
    $$files(qml/pages/*.qml) \
    $$files(qml/delegates/*.qml) \
    $$files(qml/components/*.qml) \
    $$files(qml/utils/*.qml) \
    $$files(qml/scripts/*.js) \
    rpm/$${TARGET}.yaml \
    rpm/$${TARGET}.spec \
    $${TARGET}.desktop \
    $${TARGET}.png

RESOURCES += $${TARGET}.qrc

QT += \
    network\
    sql\
    multimedia

images.files = \
    $$files(images/*.jpg) \
    $$files(images/*.png) \
    images/icons
images.path = /usr/share/$${TARGET}/images

INSTALLS += images

DEFINES += APP_VERSION=\\\"$$VERSION\\\"
