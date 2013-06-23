import QtQuick 1.1
import Sailfish.Silica 1.0

Item {
    id: songItem
    property bool menuOpen: listView.contextMenu != null && listView.contextMenu.parent === songItem
    width: listView.width
    height: menuOpen ? listView.contextMenu.height + contentItem.height : contentItem.height

    BackgroundItem {
        id: contentItem
        width: parent.width
        height: theme.itemSizeSmall

        Label {
            id: dateLabel
            text: Qt.formatDateTime(date, 'hh:mm')
            anchors {
                left: parent.left
                leftMargin: theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }
            color: theme.secondaryColor
            font.pixelSize: theme.fontSizeSmall
        }

        Column {
            width: parent.width
            anchors {
                left: dateLabel.right
                leftMargin: theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }

            Label {
                id: artistLabel
                text: artist
                font.pixelSize: theme.fontSizeSmall
                width: parent.width - dateLabel.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
            }

            Label {
                id: titleLabel
                text: title
                color: theme.secondaryColor
                font.pixelSize: theme.fontSizeExtraSmall
                width: parent.width - dateLabel.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
            }
        }

        onPressAndHold: {
            if (!listView.contextMenu)
                listView.contextMenu = contextMenuComponent.createObject(listView)
            listView.contextMenu.show(songItem)
        }

    }
}
