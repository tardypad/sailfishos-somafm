/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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
                        id: topText
                        anchors {
                            top: banner.bottom
                            topMargin: Theme.paddingSmall
                        }
                        width: parent.width
                        text: "Fully enjoy SomaFM on your mobile"
                        font.pixelSize: Theme.fontSizeSmall
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        anchors {
                            top: topText.bottom
                            topMargin: Theme.paddingSmall
                        }
                        width: parent.width
                        text: "version " + _appVersion
                        font.pixelSize: Theme.fontSizeExtraSmall
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
                    text: "The source code is available at
                          <br/><a href='https://github.com/tardypad/somafm'>https://github.com/tardypad/somafm</a>
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

                    Image {
                        anchors {
                            right: parent.right
                            rightMargin: Theme.paddingMedium
                            verticalCenter: parent.verticalCenter
                        }
                        height: Theme.iconSizeMedium
                        width: Theme.iconSizeMedium
                        source: somaTheme.getIconSource("support", "medium")
                        fillMode: Image.PreserveAspectFit
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: ExternalLinks.browse(somaTheme.supportUrl)
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
