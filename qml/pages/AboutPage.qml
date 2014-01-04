import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../components"

Page {
    property color itemBackgroundColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity / 3)

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            id: pageHeader
            title: "About"
            iconSource: "image://theme/icon-m-about"
        }
        model: VisualItemModel {
            Column {
                spacing: Theme.paddingLarge
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 2 * Theme.paddingLarge

                Rectangle {
                    color: "transparent"
                    width: parent.width
                    height: childrenRect.height

                    Banner {
                        id: banner
                        width: parent.width
                        height: Theme.itemSizeExtraLarge
                        spacing: Theme.paddingLarge
                    }

                    Label {
                        anchors {
                            top: banner.bottom
                            topMargin: Theme.paddingSmall
                        }
                        width: parent.width
                        text: "Fully enjoy SomaFM on your Jolla phone"
                        font.pixelSize: Theme.fontSizeExtraSmall
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle {
                    color: itemBackgroundColor
                    width: parent.width
                    height: childrenRect.height + 2 * Theme.paddingMedium

                    Label {
                        id: devLabel
                        anchors {
                            top: parent.top
                            topMargin: Theme.paddingMedium
                            horizontalCenter: parent.horizontalCenter
                        }
                        width: parent.width - 2 * Theme.paddingMedium
                        font.pixelSize: Theme.fontSizeSmall
                        horizontalAlignment: Text.AlignLeft
                        text: "Application Design\nApplication Development\nApplication Graphics\nApplication Testing"
                    }

                    Label {
                        id: authorLabel
                        anchors {
                            top: devLabel.bottom
                            topMargin: Theme.paddingSmall
                            horizontalCenter: parent.horizontalCenter
                        }
                        width: parent.width - 2 * Theme.paddingMedium
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
                }

                Rectangle {
                    color: itemBackgroundColor
                    width: parent.width
                    height: helpLabel.height + 2 * Theme.paddingMedium

                    Label {
                        id: helpLabel
                        anchors {
                            left: parent.left
                            leftMargin: Theme.paddingMedium
                            verticalCenter: parent.verticalCenter
                        }
                        text: "If you like the app,\nplease consider helping us"
                        font.pixelSize: Theme.fontSizeSmall
                        horizontalAlignment: Text.AlignLeft
                    }

                    IconButton {
                        anchors {
                            right: parent.right
                            rightMargin: Theme.paddingMedium
                            verticalCenter: parent.verticalCenter
                        }
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
                    spacing: Theme.paddingMedium
                    anchors.horizontalCenter: parent.horizontalCenter

                    Label {
                        text: "Support Email"
                        font.pixelSize: Theme.fontSizeSmall
                    }

                    Label {
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

                Rectangle {
                    width: parent.width
                    height: childrenRect.height
                    color: "transparent"

                    Label {
                        id: copyrightLabel
                        font.pixelSize: Theme.fontSizeExtraSmall
                        horizontalAlignment: Text.AlignHCenter
                        width: parent.width
                        text: "©2000-2013 SomaFM.com, LLC"
                    }
                    Label {
                        anchors {
                            top:  copyrightLabel.bottom
                            topMargin: Theme.paddingSmall
                        }
                        font.pixelSize: Theme.fontSizeExtraSmall
                        horizontalAlignment: Text.AlignHCenter
                        width: parent.width
                        text: "All Rights Reserved"
                    }
                }
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }

    function mailSupport() {
        Qt.openUrlExternally("mailto:dj@somafm.com?subject=[Sailfish app] ")
    }

    function mailDev() {
        Qt.openUrlExternally("mailto:damien@tardypad.me?subject=[SomaFM Sailfish app] ")
    }
}
