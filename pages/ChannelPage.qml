import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    property string id
    property string name
    property string description
    property string dj
    property url imageUrl
    property url mediumImageUrl
    property url bigImageUrl
    property string genre
    property int listeners
    property bool isFavorite

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: childrenRect.height

        PageHeader {
            id: header
            title: name
        }

        Image {
            id: channelImage
            smooth: true
            source: imageUrl
            height: screen.height / 5
            width: screen.height / 5
            fillMode: Image.PreserveAspectCrop
            clip: true
            anchors {
                left: parent.left;
                top: header.bottom;
                leftMargin: theme.paddingSmall
            }
        }

        Label {
            id: channelDescriptionLabel
            text: description
            anchors {
                left: channelImage.right;
                right: parent.right;
                top: header.bottom;
                rightMargin: theme.paddingSmall;
                leftMargin: theme.paddingSmall
            }
            color: theme.secondaryColor
            font.pixelSize: theme.fontSizeExtraSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            truncationMode: TruncationMode.Fade
            maximumLineCount: 4
        }

        Label {
            id: channelDjLabel
            text: dj ? "by " + dj : ""
            anchors {
                top: channelDescriptionLabel.bottom;
                right: parent.right;
                rightMargin: theme.paddingSmall
            }
            color: theme.secondaryColor
            font {
                pixelSize: theme.fontSizeExtraSmall;
                italic: true
            }
            horizontalAlignment: Text.AlignRight
        }

        PullDownMenu {
            MenuItem {
                text: !isFavorite ? "Add to Favorites" : "Remove from Favorites"
                onClicked: {
                    if (!isFavorite) {
                        _favoritesManager.addFavorite(id)
                        isFavorite = true
                    } else {
                        _favoritesManager.removeFavorite(id)
                        isFavorite = false
                    }
                }
            }
        }
    }
}
