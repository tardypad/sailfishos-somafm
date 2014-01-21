import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

ListItem {
    menu: contextMenu
    showMenuOnPressAndHold: false // don't use the default showMenu() without properties
    width: listView.width

    Rectangle {
        anchors.fill: parent
        opacity: isCurrent ? 0.1 : 0
        color: Theme.highlightBackgroundColor
    }

    Label {
        id: dateLabel
        text: Qt.formatDateTime(date, 'hh:mm')
        anchors {
            left: parent.left
            leftMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font.pixelSize: Theme.fontSizeSmall
    }

    Column {
        anchors {
            left: dateLabel.right
            leftMargin: Theme.paddingMedium
            right: playImage.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: artistLabel
            text: artist
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width
            truncationMode: TruncationMode.Fade
        }

        Label {
            id: titleLabel
            text: title
            color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
            width: parent.width
            truncationMode: TruncationMode.Fade
        }
    }

    Image {
        id: playImage
        source: somaTheme.getIconSource("play", "small")
        height: Theme.iconSizeSmall
        width: visible ? Theme.iconSizeSmall : 0
        anchors {
            right: bookmarkImage.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isCurrent
    }

    Image {
        id: bookmarkImage
        source: somaTheme.getIconSource("bookmark", "small")
        height: Theme.iconSizeSmall
        width: visible ? Theme.iconSizeSmall : 0
        anchors {
            right: parent.right
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isBookmark
    }

    onPressAndHold: showMenu({"isBookmark": isBookmark})

    onClicked: {
        if (isCurrent)
            channelPage.play()
    }

    function addBookmark() {
        _bookmarksManager.addBookmark(listView.model.itemAt(index))
    }

    function removeBookmark() {
        _bookmarksManager.removeBookmark(listView.model.itemAt(index))
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
            property bool isBookmark

            IconMenuItem {
                iconSource: !isBookmark ? somaTheme.getIconSource("bookmark", "small") : somaTheme.getIconSource("unbookmark", "small")
                text: !isBookmark ? "Add to bookmarks" : "Remove from bookmarks"
                onClicked: {
                    if (!isBookmark) {
                        addBookmark()
                    } else {
                        removeBookmark()
                    }
                }
            }
            IconMenuItem {
                iconSource: somaTheme.getIconSource("google", "small")
                text: "Search on Google"
                onClicked: searchGoogle()
            }
        }
    }
}
