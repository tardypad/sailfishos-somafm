import QtQuick 2.0
import Sailfish.Silica 1.0

DockedPanel {
    id: controlPanel

    property string channelId
    property alias channelName: channelLabel.text
    property alias channelImageUrl: channelImage.source

    width: parent.width
    height: Theme.itemSizeExtraLarge
    dock: Dock.Bottom

    BackgroundItem {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: Theme.secondaryHighlightColor
        }

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

        ProgressCircle {
            id: progressIndicator
            width: Theme.iconSizeLarge
            height: Theme.iconSizeLarge
            anchors.centerIn: mediaButtonPause
            Timer {
                id: progressTimer
                interval: 250
                repeat: true
                onTriggered: progressIndicator.value = (progressIndicator.value + 1/240) % 1.0
            }
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

        onClicked: goToChannelPage()
    }

    Connections {
        target: _player
        onChannelChanged: {
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
            channelId = _player.channelId()
        }
        onPlayStarted: {
            reinitProgressIndicator()
            state = "playing"
        }
        onPauseStarted: {
            reinitProgressIndicator()
            state = "pause"
        }
    }

    function reinitProgressIndicator() {
        progressIndicator.value = 0
        progressIndicator.inAlternateCycle = true
    }

    function goToChannelPage() {
        var currentPage = pageStack.currentPage
        var url = Qt.resolvedUrl("../ChannelPage.qml")
        var properties = {"id": channelId}
        if (currentPage.objectName != "ChannelPage") {
            pageStack.push(url, properties)
        } else if (currentPage.id !== channelId) {
            pageStack.replace(url, properties)
        }
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
            PropertyChanges { target: mediaButtonPlay;   visible: true }
            PropertyChanges { target: mediaButtonPause;  visible: false }
            PropertyChanges { target: progressTimer;     running: false }
        },
        State {
            name: "playing"
            PropertyChanges { target: mediaButtonPlay;   visible: false }
            PropertyChanges { target: mediaButtonPause;  visible: true }
            PropertyChanges { target: controlPanel;      open: true; restoreEntryValues: false }
            PropertyChanges { target: progressTimer;     running: true }
        }]

    onOpenChanged: if (!open && state === "playing") show()
}
