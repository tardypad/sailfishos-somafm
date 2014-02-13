/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

ListItem {
    property int idx: index
    property string artist_d: artist
    property string title_d: title
    property bool isBookmark_d: isBookmark

    menu: listView.contextMenu
    contentHeight: Theme.itemSizeSmall
    width: listView.width

    Rectangle {
        anchors.fill: parent
        opacity: isCurrent ? 0.1 : 0
        color: Theme.highlightBackgroundColor
    }

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'hh:mm')
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font.pixelSize: Theme.fontSizeSmall
    }

    Column {
        spacing: Theme.paddingSmall
        anchors {
            left: dateLabel.right
            leftMargin: Theme.paddingMedium
            right: playImage.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: artistLabel
            text: artist
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            width: parent.width
            truncationMode: TruncationMode.Fade
        }
    }

    Image {
        id: playImage
        source: somaTheme.getIconSource("play", "small")
        height: Theme.iconSizeSmall
        width: visible ? height : 0
        anchors {
            right: bookmarkImage.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isCurrent
    }

    Image {
        id: bookmarkImage
        source: somaTheme.getIconSource("bookmark", "small")
        height: Theme.iconSizeSmall
        width: visible ? height : 0
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isBookmark
    }

    onClicked: {
        if (isCurrent)
            channelPage.play()
    }
}
