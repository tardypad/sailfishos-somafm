/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

ListItem {
    id: listItem

    property int idx: index
    property string artist_d: artist
    property string title_d: title

    menu: listView.contextMenu
    contentHeight: Theme.itemSizeSmall
    width: listView.width
    enabled: listView.interactive || menuOpen

    Label {
        id: dateLabel
        text: Qt.formatDateTime(bookmarkDate, 'MMM dd')
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
        width: parent.width
        anchors {
            left: dateLabel.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: artistLabel
            text: artist
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }
    }

    onPressAndHold: songPanel.hide()

    onClicked: {
        if (songPanel.open && songPanel.isBookmarkDisplayed(artist, title)) {
            songPanel.hide()
        } else {
            songPanel.showBookmark(artist, title, album, bookmarkDate)
        }
    }

    ListView.onRemove: animateRemoval(listItem)

    function remove() {
        remorseAction("Removing bookmark", function() {
            listView._removeBookmark(index)
        });
    }
}
