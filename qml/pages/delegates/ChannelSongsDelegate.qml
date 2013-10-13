import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

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
        height: Theme.iconSizeSmall
        width: Theme.iconSizeSmall
        anchors {
            right: parent.right
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isBookmark
    }

    onPressAndHold: showMenu({"isBookmark": isBookmark})

    function addBookmark() {
        _bookmarksManager.addBookmark(listView.model.itemAt(index))
    }

    function removeBookmark() {
        _bookmarksManager.removeBookmark(listView.model.itemAt(index))
    }

    Component {
        id: contextMenu
        ContextMenu {
            property bool isBookmark

            IconMenuItem {
                iconSource: !isBookmark ? "qrc:/icon/bookmark" : "qrc:/icon/un-bookmark"
                text: !isBookmark ? "Add to bookmarks" : "Remove from bookmarks"
                onClicked: {
                    if (!isBookmark) {
                        addBookmark()
                    } else {
                        removeBookmark()
                    }
                }
            }
        }
    }
}
