import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    menu: contextMenu
    showMenuOnPressAndHold: false // don't use the default showMenu() without properties
    contentHeight: Theme.itemSizeSmall
    width: listView.width

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
        showMenu({
                     "isBookmark": isBookmark,
                     "index": index
                 })
    }

    Component {
        id: contextMenu
        ContextMenu {
            property bool isBookmark
            property int index

            IconActionMenuItem {
                iconSource: !isBookmark ? "qrc:/icon/bookmark" : "qrc:/icon/un-bookmark"
                text: !isBookmark ? "Add to bookmarks" : "Remove from bookmarks"
                onClicked: {
                    if (!isBookmark) {
                        _bookmarksManager.addBookmark(_channelSongsModel.itemAt(index))
                    } else {
                        _bookmarksManager.removeBookmark(_channelSongsModel.itemAt(index))
                    }
                }
            }
        }
    }
}
