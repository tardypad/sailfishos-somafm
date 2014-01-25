import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

import "../scripts/ExternalLinks.js" as ExternalLinks

ListItem {
    id: listItem

    menu: contextMenu
    contentHeight: Theme.itemSizeSmall
    width: listView.width
    enabled: listView.interactive || menuOpen

    Label {
        id: dateLabel
        text: Qt.formatDateTime(bookmarkDate, 'MMM dd')
        anchors {
            left: parent.left
            leftMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font.pixelSize: Theme.fontSizeSmall
    }

    Column {
        width: parent.width
        anchors {
            left: dateLabel.right
            leftMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: artistLabel
            text: artist
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width - dateLabel.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            width: parent.width - dateLabel.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }
    }

    onPressAndHold: songPanel.hide()

    onClicked: {
        if (songPanel.open && songPanel.index === index) {
            songPanel.hide()
        } else {
            songPanel.showBookmark(index, artist, title, album, bookmarkDate)
        }
    }

    ListView.onRemove: animateRemoval(listItem)

    function _removeBookmark() {
        remorseAction("Removing bookmark", function() {
            listView.model.removeBookmark(listView.model.itemAt(index))
        })
    }

    function _searchGoogle() {
        ExternalLinks.searchGoogle([artist, title])
    }

    Component {
        id: contextMenu
        ContextMenu {
            IconMenuItem {
                iconSource: "unbookmark"
                text: "Remove from bookmarks"
                onClicked: _removeBookmark()
            }
            IconMenuItem {
                iconSource: "google"
                text: "Search on Google"
                onClicked: _searchGoogle()
            }
        }
    }
}
