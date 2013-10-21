import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property alias channelName: channelLabel.text
    property alias channelImageUrl: channelImage.source

    id: controlPanel
    width: parent.width
    height: Theme.itemSizeExtraLarge

    Image {
        id: channelImage
        height: Theme.iconSizeLarge
        width: Theme.iconSizeLarge
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }

        BusyIndicator {
            size: BusyIndicatorSize.Small
            running: channelImage.status === Image.Loading
            anchors.centerIn: parent
        }
    }

    Label {
        id: channelLabel
        anchors {
            left: channelImage.right
            leftMargin: Theme.paddingMedium
            right: mediaButton.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 2
    }

    IconButton {
        id: mediaButton
        icon.source: "image://theme/icon-l-play"
        icon.width: Theme.iconSizeLarge
        icon.height: Theme.iconSizeLarge
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
    }

    Connections {
        target: _player
        onChannelChanged: {
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
        }
    }
}
