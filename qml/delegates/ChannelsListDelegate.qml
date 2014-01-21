import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../components"

ListItem {
    menu: contextMenu
    showMenuOnPressAndHold: false // don't use the default showMenu() without properties
    contentHeight: Theme.itemSizeLarge
    width: listView.width

    ChannelImage {
        id: channelImage
        size: BusyIndicatorSize.Small
        source: imageUrl
        height: parent.height - Theme.paddingSmall*2
        width: parent.height - Theme.paddingSmall*2
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: Theme.paddingSmall
        }
    }

    Image {
        id: favoriteImage
        source: somaTheme.getIconQrc("favorite", "small")
        height: Theme.iconSizeSmall * 0.75
        width: visible ? Theme.iconSizeSmall * 0.75 : 0
        anchors {
            left: channelImage.right
            leftMargin: Theme.paddingSmall
            verticalCenter: channelNameLabel.verticalCenter
        }
        fillMode: Image.PreserveAspectFit
        visible: isBookmark
    }

    Label {
        id: channelNameLabel
        text: name
        anchors {
            left: favoriteImage.right
            leftMargin: Theme.paddingSmall
            top: parent.top
        }
        color: highlighted ? Theme.highlightColor : Theme.primaryColor
    }

    Label {
        id: channelDescriptionLabel
        text: description
        anchors {
            left: channelImage.right
            right: parent.right
            top: channelNameLabel.bottom
            topMargin: -Theme.paddingSmall
            leftMargin: Theme.paddingSmall
        }
        color: highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 2
    }

    onPressAndHold: {
        showMenu({
                     "isFavorite": isBookmark,
                     "isPlaying" : _player.isPlaying(id)
                 })
    }

    onClicked: goToChannelPage()

    function goToChannelPage() {
        pageStack.push(Qt.resolvedUrl("../pages/ChannelPage.qml"), {"id": id})
    }

    function play() {
        _player.play(listView.model.itemAt(index))
    }

    function pause() {
        _player.pause()
    }

    function addFavorite() {
        _favoritesManager.addFavorite(listView.model.itemAt(index))
    }

    function removeFavorite() {
        _favoritesManager.removeFavorite(listView.model.itemAt(index))
    }

    Component {
        id: contextMenu
        ContextMenu {
            property bool isFavorite
            property bool isPlaying

            IconMenuItem {
                iconSource: !isPlaying ? somaTheme.getIconQrc("play", "small") : somaTheme.getIconQrc("pause", "small")
                text: !isPlaying ? "Play" : "Pause"
                onClicked: {
                    if (!isPlaying) {
                        play()
                    } else {
                        pause()
                    }
                }
            }

            IconMenuItem {
                iconSource: !isFavorite ? somaTheme.getIconQrc("favorite", "small") : somaTheme.getIconQrc("unfavorite", "small")
                text: !isFavorite ? "Add to favorites" : "Remove from favorites"
                onClicked: {
                    if (!isFavorite) {
                        addFavorite()
                    } else {
                        removeFavorite()
                    }
                }
            }
        }
    }
}
