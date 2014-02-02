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

import "../scripts/ExternalLinks.js" as ExternalLinks

Page {
    property color _itemBackgroundColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity / 3)

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            id: pageHeader
            title: "About"
            iconSource: "about"
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
                        text: "Fully enjoy SomaFM on your Jolla"
                        font.pixelSize: Theme.fontSizeSmall
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                AuthorRectangle {
                    id: authorRect
                    color: _itemBackgroundColor
                }

                Label {
                    id: codeLabel
                    width: parent.width
                    text: "The source code is available under MIT license
                          <br/><a href='https://github.com/tardypad/somafm'>https://github.com/tardypad/somafm</a>
                          <br/>
                          <br/>You can contact me for any remarks,
                          <br/>bugs, feature requests, ideas,... "
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.pixelSize: Theme.fontSizeExtraSmall
                    horizontalAlignment: Text.AlignHCenter
                    textFormat: Text.StyledText
                    linkColor: Theme.highlightColor
                    onLinkActivated: ExternalLinks.browse(link)
                }

                Rectangle {
                    color: _itemBackgroundColor
                    width: parent.width
                    height: helpLabel.height + 2 * Theme.paddingMedium

                    Label {
                        id: helpLabel
                        anchors {
                            left: parent.left
                            leftMargin: Theme.paddingMedium
                            verticalCenter: parent.verticalCenter
                        }
                        text: "If you like the app,\nplease consider helping SomaFM"
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
                            source: somaTheme.getIconSource("support", "medium")
                            fillMode: Image.PreserveAspectFit
                        }
                        onClicked: pageStack.push(Qt.resolvedUrl("SupportPage.qml"))
                    }
                }

                Label {
                    id: enjoyLabel
                    width: parent.width
                    text: "Enjoy!"
                    font.pixelSize: Theme.fontSizeLarge
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
