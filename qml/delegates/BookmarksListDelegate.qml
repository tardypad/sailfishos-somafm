import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

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
            showSongPanel()
        }
    }

    function showSongPanel() {
        songPanel.index = index
        songPanel.title = title
        songPanel.artist = artist
        songPanel.album = album
        songPanel.date = Qt.formatDateTime(bookmarkDate, 'ddd dd MMM, hh:mm')
        songPanel.show()
    }

    ListView.onRemove: animateRemoval(listItem)

    function remove() {
        remorseAction("Removing bookmark", function() {
            listView.model.removeBookmark(listView.model.itemAt(index))
        })
    }

    function searchGoogle() {
        var url = "http://www.google.com/search?q="+encodeURIComponent(artist)+"+"+encodeURIComponent(title)
        console.log("open search Google page in browser")
        console.log(url)
        Qt.openUrlExternally(url)
    }

    Component {
        id: contextMenu
        ContextMenu {
            IconMenuItem {
                iconSource: somaTheme.getIconQrc("unbookmark", "small")
                text: "Remove from bookmarks"
                onClicked: remove()
            }
            IconMenuItem {
                iconSource: somaTheme.getIconQrc("google", "small")
                text: "Search on Google"
                onClicked: searchGoogle()
            }
        }
    }
}
