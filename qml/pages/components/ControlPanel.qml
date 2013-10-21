import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: controlPanel

    property string channelName
    property url channelImageUrl

    width: parent.width
    height: Theme.itemSizeExtraLarge
    enabled: false

    onEnabledChanged: {
        if (enabled && !_content) {
            _content = activeContent.createObject(controlPanel)
        }
    }

    property Item _content

    Component {
        id: activeContent

        Item {
            anchors.fill: parent

            Image {
                id: channelImage
                source: channelImageUrl
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
                text: channelName
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
        }
    }

    Connections {
        target: _player
        onChannelChanged: {
            enabled = true
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
        }
    }
}
