import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

ListItem {
    menu: contextMenu
    showMenuOnPressAndHold: false // don't use the default showMenu() without properties
    contentHeight: Theme.itemSizeLarge
    width: listView.width

    Image {
        id: channelImage
        smooth: true
        source: imageUrl
        height: parent.height - Theme.paddingSmall*2
        width: parent.height - Theme.paddingSmall*2
        fillMode: Image.PreserveAspectCrop
        clip: true
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: Theme.paddingSmall
        }

        BusyIndicator {
            size: BusyIndicatorSize.Small
            running: channelImage.status === Image.Loading
            anchors.centerIn: parent
        }
    }

    Label {
        id: channelNameLabel
        text: name
        anchors {
            left: channelImage.right
            leftMargin: Theme.paddingSmall
            top: parent.top
        }
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
        color: Theme.secondaryColor
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 2
    }

    onPressAndHold: showMenu({"isFavorite": isBookmark})

    onClicked: {
        pageStack.push(Qt.resolvedUrl("../ChannelPage.qml"),
                       {
                           "channelIndex": index,
                           'id' : id,
                           'name': name,
                           'description': description,
                           'dj': dj,
                           'imageUrl': imageUrl,
                           'mediumImageUrl': imageMediumUrl,
                           'bigImageUrl': imageBigUrl,
                           'genres': genres,
                           'listeners': listeners,
                           'isFavorite': isBookmark
                       }
                       )
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

            IconMenuItem {
                iconSource: !isFavorite ? "qrc:/icon/favorite" : "qrc:/icon/un-favorite"
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
