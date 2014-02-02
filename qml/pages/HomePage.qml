/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


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
                source: somaTheme.getImageSource("name")
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
                source: somaTheme.getImageSource("background")
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
                iconSource: "settings"
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
                inPullDown: true
            }
            IconMenuItem {
                text: "Song bookmarks"
                iconSource: "bookmark"
                onClicked: pageStack.push(Qt.resolvedUrl("BookmarksPage.qml"))
                inPullDown: true
            }
            IconMenuItem {
                text: "News"
                iconSource: "news"
                onClicked: pageStack.push(Qt.resolvedUrl("NewsPage.qml"))
                inPullDown: true
            }
        }

        PushUpMenu {
            IconMenuItem {
                text: "About"
                iconSource: "about"
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
