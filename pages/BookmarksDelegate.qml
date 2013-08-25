import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    menu: contextMenu
    showMenuOnPressAndHold: false // don't use the default showMenu() without properties
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

    onPressAndHold: {
        showMenu({"index": index})
    }

    Component {
        id: contextMenu
        ContextMenu {
            property int index

            IconActionMenuItem {
                iconSource: "qrc:/icon/un-bookmark"
                text: "Remove from bookmarks"
                onClicked: _bookmarksManager.removeBookmark(_bookmarksManager.itemAt(index))
            }
        }
    }
}
