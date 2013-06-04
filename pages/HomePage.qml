import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    id: homePage

    // Second page to load on startup
    property Page secondPage

    Rectangle {
        color: "black"
        anchors.fill: parent

        Image {
            id: homeName
            source: "qrc:/images/name"
            smooth: true
            width: parent.width * 0.9
            height: parent.height * 0.2
            fillMode: Image.PreserveAspectFit
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.05
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Image {
            id: homeBackground
            source: "qrc:/images/background"
            smooth: true
            width: parent.width
            height: parent.height * 0.6
            fillMode: Image.PreserveAspectCrop
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.15
        }

        Text {
            id: homeText
            text: "Listener-supported,\ncommercial-free,\nunderground/alternative\nradio broadcasting\n from San Francisco"
            color: "white"
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: theme.fontSizeSmall
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: parent.height * 0.1
        }
    }

    onStatusChanged: {
        if (status == PageStatus.Active) {
            if (secondPage === null) {
                // Create second page on startup
                secondPage = pageStack.pushExtra(Qt.resolvedUrl("PopularityPage.qml"))
                secondPage.createObject
            }
            // Second page accessible with a flick
            pageStack.forwardNavigation = true
        } else if (status == PageStatus.Inactive) {
            // don't loop pages
            pageStack.forwardNavigation = false
        }
    }
}
