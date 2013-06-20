import QtQuick 1.1
import Sailfish.Silica 1.0

Item {
    height: childrenRect.height
    width: parent.width

    PageHeader {
        id: header
        title: name
    }

    Image {
        id: channelImage
        smooth: true
        source: imageUrl
        height: theme.itemSizeLarge * 2
        width: theme.itemSizeLarge * 2
        fillMode: Image.PreserveAspectCrop
        clip: true
        anchors {
            left: parent.left;
            top: header.bottom;
            leftMargin: theme.paddingSmall
        }
    }

    Image {
        id: favoriteImage
        source: "qrc:/icons/favorites"
        height: header.height / 4
        width: header.height / 4
        anchors {
            top: header.top
            right: header.right
            topMargin: theme.paddingSmall
            rightMargin: theme.paddingSmall
        }
        fillMode: Image.PreserveAspectFit
        visible: isFavorite
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
}
