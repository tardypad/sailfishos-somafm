import QtQuick 2.0
import Sailfish.Silica 1.0

DockedPanel {
    id: controlPanel

    property alias channelName: channelLabel.text
    property alias channelImageUrl: channelImage.source

    width: parent.width
    height: Theme.itemSizeExtraLarge
    dock: Dock.Bottom

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
            right: mediaButtonPause.left
            rightMargin: Theme.paddingMedium
            verticalCenter: parent.verticalCenter
        }
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        truncationMode: TruncationMode.Fade
        maximumLineCount: 2
    }

    IconButton {
        id: mediaButtonPause
        icon.width: Theme.iconSizeLarge
        icon.height: Theme.iconSizeLarge
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        icon.asynchronous: true
        icon.source: "image://theme/icon-l-pause"
        onClicked: pause()
    }

    IconButton {
        id: mediaButtonPlay
        icon.width: Theme.iconSizeLarge
        icon.height: Theme.iconSizeLarge
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
            verticalCenter: parent.verticalCenter
        }
        icon.asynchronous: true
        icon.source: "image://theme/icon-l-play"
        onClicked: play()
    }

    Connections {
        target: _player
        onChannelChanged: {
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
        }
        onPlayStarted: state = "playing"
        onPauseStarted: state = "pause"
    }

    function pause() {
        _player.pause()
    }

    function play() {
        _player.play()
    }

    states: [
        State {
            name: "pause"
            PropertyChanges {
                target: mediaButtonPlay
                visible: true
            }
            PropertyChanges {
                target: mediaButtonPause
                visible: false
            }
        },
        State {
            name: "playing"
            PropertyChanges {
                target: mediaButtonPlay
                visible: false
            }
            PropertyChanges {
                target: mediaButtonPause
                visible: true
            }
            PropertyChanges {
                target: controlPanel
                open: true
                restoreEntryValues: false
            }
        }]

    onOpenChanged: if (!open && state === "playing") show()
}
