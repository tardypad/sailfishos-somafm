import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: songItem
    property bool menuOpen: listView.contextMenu != null && listView.contextMenu.parent === songItem
    width: listView.width
    height: menuOpen ? listView.contextMenu.height + contentItem.height : contentItem.height

    BackgroundItem {
        id: contentItem
        width: parent.width
        height: Theme.itemSizeSmall

        Label {
            id: dateLabel
            text: Qt.formatDateTime(date, 'hh:mm')
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

        Image {
            id: bookmarkImage
            source: "qrc:/icon/bookmark"
            height: parent.height / 3
            width: parent.height / 3
            anchors {
                right: parent.right
                rightMargin: Theme.paddingMedium
                verticalCenter: parent.verticalCenter
            }
            fillMode: Image.PreserveAspectFit
            visible: isBookmark
        }

        onPressAndHold: {
            if (!listView.contextMenu)
                listView.contextMenu = contextMenuComponent.createObject(listView)
            listView.contextMenu.isBookmark = isBookmark
            listView.contextMenu.index = index
            listView.contextMenu.show(songItem)
        }

    }
}
