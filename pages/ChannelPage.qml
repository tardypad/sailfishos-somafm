import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    property string name
    property string description
    property string dj
    property url imageUrl
    property url mediumImageUrl
    property url bigImageUrl
    property string genre
    property int listeners

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
            anchors.left: parent.left
            anchors.leftMargin: theme.paddingSmall
            anchors.top: header.bottom
        }

        Label {
            id: channelDescriptionLabel
            text: description
            anchors.left: channelImage.right
            anchors.right: parent.right
            anchors.top: header.bottom
            anchors.rightMargin: theme.paddingSmall
            anchors.leftMargin: theme.paddingSmall
            color: theme.secondaryColor
            font.pixelSize: theme.fontSizeExtraSmall
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            truncationMode: TruncationMode.Fade
            maximumLineCount: 4
        }

        Label {
            id: channelDjLabel
            text: dj ? "by " + dj : ""
            anchors.top: channelDescriptionLabel.bottom
            anchors.right: parent.right
            anchors.rightMargin: theme.paddingSmall
            color: theme.secondaryColor
            font.pixelSize: theme.fontSizeExtraSmall
            font.italic: true
            horizontalAlignment: Text.AlignRight
        }

        PullDownMenu {
            MenuItem {
                text: "Add to Favorites"
                onClicked: console.log("add to favorites")
            }
        }
    }
}
