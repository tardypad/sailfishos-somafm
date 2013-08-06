import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    height: childrenRect.height
    width: listView.width

    PageHeader {
        id: header
        title: name
    }

    Image {
        id: channelImage
        smooth: true
        source: imageUrl
        height: Theme.itemSizeLarge * 2
        width: Theme.itemSizeLarge * 2
        fillMode: Image.PreserveAspectCrop
        clip: true
        anchors {
            left: parent.left
            top: header.bottom
            leftMargin: Theme.paddingSmall
        }
    }

    Image {
        id: favoriteImage
        source: "qrc:/icon/favorite"
        height: header.height / 4
        width: header.height / 4
        anchors {
            top: header.top
            right: header.right
            topMargin: Theme.paddingSmall
            rightMargin: Theme.paddingSmall
        }
        fillMode: Image.PreserveAspectFit
        visible: isFavorite
    }

    Label {
        id: channelDescriptionLabel
        text: description
        anchors {
            left: channelImage.right
            right: parent.right
            top: header.bottom
            rightMargin: Theme.paddingSmall
            leftMargin: Theme.paddingSmall
        }
        color: Theme.secondaryColor
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 4
    }

    Label {
        id: channelDjLabel
        text: dj ? "by " + dj : ""
        anchors {
            top: channelDescriptionLabel.bottom
            right: parent.right
            rightMargin: Theme.paddingSmall
        }
        color: Theme.secondaryColor
        font {
            pixelSize: Theme.fontSizeExtraSmall
            italic: true
        }
        horizontalAlignment: Text.AlignRight
    }
}
