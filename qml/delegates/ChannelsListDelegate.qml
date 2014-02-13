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

        Row {
            spacing: Theme.paddingSmall
            anchors.left: parent.left

            Image {
                id: favoriteImage
                source: somaTheme.getIconSource("favorite", "small")
                height: Theme.iconSizeSmall
                width: height
                anchors.verticalCenter: channelNameLabel.verticalCenter
                fillMode: Image.PreserveAspectFit
                visible: isBookmark
            }

            Label {
                id: channelNameLabel
                text: name
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
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
