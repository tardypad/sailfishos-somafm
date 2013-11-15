import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"

Page {
    IconPageHeader {
        id: pageHeader
        anchors {
            top: parent.top
            left: parent.left
        }
        text: "About"
        iconSource: "image://theme/icon-m-about"
    }

    Rectangle {
        id: banner
        anchors.top: pageHeader.bottom
        width: parent.width
        height: Theme.itemSizeExtraLarge
        color: "black"

        Row {
            spacing: Theme.paddingLarge
            anchors.centerIn: parent

            Image {
                id: logoImage
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/image/logo"
                smooth: true
                fillMode: Image.PreserveAspectFit
                height: banner.height * 0.8
                width: banner.width * 0.2
            }

            Image {
                id: nameImage
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/image/name"
                smooth: true
                fillMode: Image.PreserveAspectFit
                height: banner.height * 0.8
                width: banner.width * 0.6
            }
        }
    }

    Label {
        id: descriptionLabel
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: banner.bottom
            topMargin: Theme.paddingMedium
        }
        width: parent.width
        text: "Fully enjoy SomaFM on your Jolla phone"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeSmall
    }

    Label {
        id: devLabel
        anchors {
            top: descriptionLabel.bottom
            topMargin: 2 * Theme.paddingLarge
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 2 * Theme.paddingLarge
        font.pixelSize: Theme.fontSizeSmall
        horizontalAlignment: Text.AlignLeft
        text: "Application Development\nApplication Graphics\nApplication Design"
    }

    Label {
        id: authorLabel
        anchors {
            top: devLabel.bottom
            topMargin: Theme.paddingSmall
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 2 * Theme.paddingLarge
        font {
            italic: true
            pixelSize: Theme.fontSizeExtraSmall
        }
        color: Theme.highlightColor
        horizontalAlignment: Text.AlignRight
        text: "by Damien Tardy-Panis"

        MouseArea {
            anchors.fill: parent
            onClicked: mailDev()
        }
    }

    Row {
        spacing: Theme.paddingMedium
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: authorLabel.bottom
            topMargin: Theme.paddingLarge
        }

        Label {
            id: helpLabel
            anchors.verticalCenter: parent.verticalCenter
            text: "If you like the app,\nplease consider helping us"
            font.pixelSize: Theme.fontSizeSmall
            horizontalAlignment: Text.AlignRight
        }

        IconButton {
            anchors.verticalCenter: parent.verticalCenter
            icon {
                height: Theme.iconSizeMedium
                width: Theme.iconSizeMedium
                source: "image://theme/icon-m-like"
                fillMode: Image.PreserveAspectFit
            }
            onClicked: pageStack.push(Qt.resolvedUrl("SupportPage.qml"))
        }
    }

    Row {
        id: supportRow
        spacing: Theme.paddingMedium
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: copyrightLabel.top
            bottomMargin: Theme.paddingMedium
        }

        Label {
            id: supportLabel
            text: "Support Email"
            font.pixelSize: Theme.fontSizeSmall
        }

        Label {
            id: supportEmailLabel
            text: "dj@somafm.com"
            color: Theme.highlightColor
            font {
                italic: true
                pixelSize: Theme.fontSizeSmall
            }

            MouseArea {
                anchors.fill: parent
                onClicked: mailSupport()
            }
        }
    }

    Label {
        id: copyrightLabel
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: Theme.paddingLarge
        }
        font.pixelSize: Theme.fontSizeExtraSmall
        horizontalAlignment: Text.AlignHCenter
        width: parent.width
        text: "©2000-2013 SomaFM.com, LLC\nAll Rights Reserved"
    }

    function mailSupport() {
        Qt.openUrlExternally("mailto:dj@somafm.com?subject=[Sailfish app] ")
    }

    function mailDev() {
        Qt.openUrlExternally("mailto:damien@tardypad.me?subject=[SomaFM Sailfish app] ")
    }
}
