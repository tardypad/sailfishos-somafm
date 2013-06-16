import QtQuick 1.1
import Sailfish.Silica 1.0

Page {

    Rectangle {
        color: "black"
        anchors.fill: parent
        z: 0
    }

    Image {
        id: homeName
        source: "qrc:/images/name"
        smooth: true
        width: parent.width * 0.8
        height: parent.height * 0.2
        fillMode: Image.PreserveAspectFit
        anchors {
            top: parent.top;
            topMargin: parent.height * 0.05;
            horizontalCenter: parent.horizontalCenter
        }
        z: 3
    }

    Image {
        id: homeBackground
        source: "qrc:/images/background"
        smooth: true
        width: parent.width
        height: parent.height * 0.6
        fillMode: Image.PreserveAspectCrop
        clip: true
        anchors {
            bottom: parent.bottom;
            bottomMargin: parent.height * 0.15
        }
        z: 1

        Rectangle {
            width: parent.width
            height: parent.height * 0.2
            gradient: Gradient {
                GradientStop { position: 0; color: "black" }
                GradientStop { position: 1; color: "transparent" }
            }
            anchors {
                top: parent.top
            }
            z: 2
        }

        Rectangle {
            width: parent.width
            height: parent.height * 0.2
            gradient: Gradient {
                GradientStop { position: 0; color: "transparent" }
                GradientStop { position: 1; color: "black" }
            }
            anchors {
                bottom: parent.bottom
            }
            z: 2
        }
    }

    Text {
        id: homeText
        text: "Listener-supported,\ncommercial-free,\nunderground/alternative\nradio broadcasting\n from San Francisco"
        color: "white"
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: theme.fontSizeSmall
        anchors {
            bottom: parent.bottom;
            bottomMargin: parent.height * 0.1
        }
        z: 3
    }

    onReleased: pageStack.push(Qt.resolvedUrl("FavoritesPage.qml"))
}
