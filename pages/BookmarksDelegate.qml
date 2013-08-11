import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: bookmarkItem
    property bool menuOpen: listView.contextMenu != null && listView.contextMenu.parent === bookmarkItem
    width: listView.width
    height: menuOpen ? listView.contextMenu.height + contentItem.height : contentItem.height

    BackgroundItem {
        id: contentItem
        width: parent.width
        height: Theme.itemSizeSmall

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
            if (!listView.contextMenu)
                listView.contextMenu = contextMenuComponent.createObject(listView)
            listView.contextMenu.index = index
            listView.contextMenu.show(bookmarkItem)
        }

    }
}
