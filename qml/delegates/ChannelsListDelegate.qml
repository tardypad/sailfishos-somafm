/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../components"

ListItem {
    property int idx: index
    property bool isFavorite: isBookmark
    property string channelId: id
    property bool showListeners: false

    property alias column: column

    menu: listView.contextMenu
    contentHeight: Theme.itemSizeExtraLarge
    width: listView.width

    ChannelImage {
        id: channelImage
        size: BusyIndicatorSize.Small
        source: imageUrl
        height: parent.height
        width: height
        anchors.left: parent.left
    }

    Column {
        id: column
        spacing: Theme.paddingSmall
        anchors {
            left: channelImage.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }

        Item {
            width: parent.width
            height: channelNameLabel.height

            Image {
                id: favoriteImage
                source: somaTheme.getIconSource("favorite", "small")
                height: Theme.iconSizeSmall
                width: visible ? height : 0
                anchors.left: parent.left
                fillMode: Image.PreserveAspectFit
                visible: isBookmark
            }

            Label {
                id: channelNameLabel
                text: name
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
                truncationMode: TruncationMode.Fade
                anchors {
                    left: favoriteImage.right
                    leftMargin: favoriteImage.visible ? Theme.paddingSmall : 0
                    right: channelListenersLabel.left
                    rightMargin: channelListenersLabel.visible ? Theme.paddingSmall : 0
                    verticalCenter: favoriteImage.verticalCenter
                }
            }

            Label {
                id: channelListenersLabel
                text: listeners
                anchors {
                    right: listenerIcon.left
                    rightMargin: Theme.paddingSmall
                    verticalCenter: favoriteImage.verticalCenter
                }
                width: visible ? implicitWidth : 0
                color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                font {
                    pixelSize: Theme.fontSizeExtraSmall * 0.8;
                    italic: true
                }
                visible: showListeners
            }

            Image {
                id: listenerIcon
                source: somaTheme.getIconSource("listener", "small")
                smooth: true
                height: Theme.iconSizeSmall * 0.8
                width: visible ? height : 0
                anchors {
                    right: parent.right
                    verticalCenter: favoriteImage.verticalCenter
                }
                opacity: 0.1 + (listeners / maximumListeners) * 0.9
                fillMode: Image.PreserveAspectFit
                visible: showListeners
            }
        }

        Label {
            id: channelDescriptionLabel
            width: parent.width
            text: description
            color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            truncationMode: TruncationMode.Fade
            maximumLineCount: 2
        }
    }

    onClicked: listView._goToChannelPage(id)
}
