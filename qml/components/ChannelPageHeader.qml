import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    height: childrenRect.height
    width: listView.width

    PageHeader {
        id: header
        title: name

        Image {
            id: favoriteImage
            source: somaTheme.getIconSource("favorite", "small")
            height: Theme.iconSizeSmall
            width: Theme.iconSizeSmall
            anchors {
                right: header._titleItem.left
                rightMargin: Theme.paddingSmall
                verticalCenter: header._titleItem.verticalCenter
            }
            fillMode: Image.PreserveAspectFit
            visible: isFavorite
        }
    }

    ChannelImage {
        id: channelImage
        size: BusyIndicatorSize.Medium
        source: imageUrl
        height: Theme.itemSizeLarge * 2
        width: Theme.itemSizeLarge * 2
        anchors {
            left: parent.left
            top: header.bottom
            leftMargin: Theme.paddingSmall
        }
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
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 4
    }

    Label {
        id: channelDjLabel
        text: "by " + dj
        anchors {
            top: channelDescriptionLabel.bottom
            right: mailButton.left
            rightMargin: Theme.paddingMedium
        }
        color: Theme.highlightColor
        font {
            pixelSize: Theme.fontSizeExtraSmall
            italic: true
        }
        visible: dj
        horizontalAlignment: Text.AlignRight

        MouseArea {
            anchors.fill: parent
            onClicked: mailDj()
        }
    }

    IconButton {
        id: mailButton
        anchors {
            right: parent.right
            rightMargin: Theme.paddingSmall
            verticalCenter: channelDjLabel.verticalCenter
        }
        height: Theme.iconSizeSmall / 2
        width: Theme.iconSizeSmall / 2
        icon {
            source: somaTheme.getIconSource("mail", "small")
            height: Theme.iconSizeSmall / 2
            fillMode: Image.PreserveAspectFit
        }
        visible: dj
        onClicked: mailDj()
    }

    function mailDj() {
        if (djMail)
            Qt.openUrlExternally("mailto:"+djMail+"?subject=["+name+"] ")
    }
}
