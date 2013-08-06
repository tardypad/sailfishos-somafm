import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: childrenRect.height

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

            Text {
                id: homeText
                text: "Listener-supported,\ncommercial-free,\nunderground/alternative\nradio"
                color: "white"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Theme.fontSizeSmall
                anchors {
                    bottom: homeTextExtra.top
                    bottomMargin: Theme.paddingMedium
                }
                z: 3
            }

            Text {
                id: homeTextExtra
                text: "broadcasting from San Francisco"
                color: "white"
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

        PullDownMenu {
            IconPageMenuItem {
                text: "News"
                iconSource: "qrc:/icon/news"
                nextPage: "NewsPage.qml"
                isReplace: false
            }
            IconPageMenuItem {
                text: "Song bookmarks"
                iconSource: "qrc:/icon/bookmark"
                nextPage: "BookmarksPage.qml"
                isReplace: false
            }
        }

        PushUpMenu {
            bottomMargin: topMargin

            Label {
                text: "©2000-2013 SomaFM.com"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
