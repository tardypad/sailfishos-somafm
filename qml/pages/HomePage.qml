import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../components"

Page {

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: Screen.height

        Rectangle {
            color: "black"
            width: Screen.width
            height: Screen.height
            anchors.top: parent.top
            z: 0

            Image {
                id: homeName
                source: "qrc:/image/name"
                smooth: true
                width: parent.width * 0.8
                height: parent.height * 0.2
                fillMode: Image.PreserveAspectFit
                anchors {
                    top: parent.top
                    topMargin: parent.height * 0.05
                    horizontalCenter: parent.horizontalCenter
                }
                z: 3
            }

            Image {
                id: homeBackground
                source: "qrc:/image/background"
                smooth: true
                width: parent.width
                height: parent.height * 0.6
                fillMode: Image.PreserveAspectCrop
                clip: true
                anchors {
                    bottom: parent.bottom
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

            Label {
                id: homeText
                text: "Listener-supported,\ncommercial-free,\nunderground/alternative\nradio"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Theme.fontSizeSmall
                anchors {
                    bottom: homeTextExtra.top
                    bottomMargin: Theme.paddingMedium
                }
                z: 3
            }

            Label {
                id: homeTextExtra
                text: "broadcasting from San Francisco"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Theme.fontSizeExtraSmall
                anchors {
                    bottom: parent.bottom
                    bottomMargin: parent.height * 0.1
                }
                z: 3
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var nextPage = _favoritesManager.isEmpty() ? "PopularsPage.qml" : "FavoritesPage.qml"
                    pageStack.push(Qt.resolvedUrl(nextPage))
                }
            }
        }

        InternetLinksPanel {
            id: linksPanel
        }

        PullDownMenu {
            IconMenuItem {
                text: "Settings"
                iconSource: "image://theme/icon-camera-settings"
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
            IconMenuItem {
                text: "Song bookmarks"
                iconSource: "qrc:/icon/bookmark"
                onClicked: pageStack.push(Qt.resolvedUrl("BookmarksPage.qml"))
            }
            IconMenuItem {
                text: "News"
                iconSource: "qrc:/icon/news"
                onClicked: pageStack.push(Qt.resolvedUrl("NewsPage.qml"))
            }
        }

        PushUpMenu {
            IconMenuItem {
                text: "About"
                iconSource: "image://theme/icon-m-about"
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }
    }

    onStatusChanged: {
        switch (status) {
        case PageStatus.Active:
            linksPanel.show()
            break
        case PageStatus.Inactive:
            linksPanel.hide()
            break
        }
    }
}
