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

    menu: listView.contextMenu
    contentHeight: Theme.itemSizeLarge
    width: listView.width

    ChannelImage {
        id: channelImage
        size: BusyIndicatorSize.Small
        source: imageUrl
        height: parent.height - Theme.paddingSmall*2
        width: parent.height - Theme.paddingSmall*2
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: Theme.paddingSmall
        }
    }

    Image {
        id: favoriteImage
        source: somaTheme.getIconSource("favorite", "small")
        height: Theme.iconSizeSmall * 0.75
        width: visible ? Theme.iconSizeSmall * 0.75 : 0
        anchors {
            left: channelImage.right
            leftMargin: Theme.paddingSmall
            verticalCenter: channelNameLabel.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isBookmark
    }

    Label {
        id: channelNameLabel
        text: name
        anchors {
            left: favoriteImage.right
            leftMargin: Theme.paddingSmall
            top: parent.top
        }
        color: highlighted ? Theme.highlightColor : Theme.primaryColor
    }

    Label {
        id: channelDescriptionLabel
        text: description
        anchors {
            left: channelImage.right
            right: parent.right
            top: channelNameLabel.bottom
            topMargin: -Theme.paddingSmall
            leftMargin: Theme.paddingSmall
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 2
    }

    onClicked: listView._goToChannelPage(id)
}
