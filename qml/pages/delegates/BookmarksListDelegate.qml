import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

ListItem {
    id: listItem
    menu: contextMenu
    contentHeight: Theme.itemSizeSmall
    width: listView.width

    Label {
        id: dateLabel
        text: Qt.formatDateTime(bookmarkDate, 'MMM dd')
        anchors {
            left: parent.left
            leftMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        color: Theme.secondaryColor
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
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width - dateLabel.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: Theme.secondaryColor
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
        var url = "http://www.google.com/search?q="+artist+"+"+title
        console.log("open search Google page in browser")
        console.log(url)
        Qt.openUrlExternally(url)
    }

    Component {
        id: contextMenu
        ContextMenu {
            IconMenuItem {
                iconSource: "qrc:/icon/un-bookmark"
                text: "Remove from bookmarks"
                onClicked: remove()
            }
            IconMenuItem {
                iconSource: "qrc:/icon/google"
                text: "Search on Google"
                onClicked: searchGoogle()
            }
        }
    }
}
