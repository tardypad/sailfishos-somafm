import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

DockedPanel {
    id: controlPanel

    property string channelId
    property alias channelName: channelLabel.text
    property alias channelImageUrl: channelImage.source
    property alias artist: artistLabel.text
    property alias song: songLabel.text

    signal close

    state: "pause"

    width: parent.width
    height: backgroundItem.height
    contentHeight: height
    flickableDirection: Flickable.VerticalFlick
    dock: Dock.Bottom

    BackgroundItem {
        id: backgroundItem
        width: parent.width
        height: Theme.itemSizeExtraLarge

        Rectangle {
            anchors.fill: parent
            color: Theme.secondaryHighlightColor
        }

        ChannelImage {
            id: channelImage
            size: BusyIndicatorSize.Small
            height: parent.height - Theme.paddingSmall*2
            width: height
            anchors {
                left: parent.left
                leftMargin: Theme.paddingSmall
                verticalCenter: parent.verticalCenter
            }
        }

        Label {
            id: channelLabel
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                top: parent.top
                topMargin: Theme.paddingSmall
            }
            truncationMode: TruncationMode.Fade
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: artistLabel
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                bottom: songLabel.top
                bottomMargin: -Theme.paddingSmall
            }
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeExtraSmall
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: songLabel
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                bottom: parent.bottom
                bottomMargin: Theme.paddingMedium
            }
            truncationMode: TruncationMode.Fade
            font{
                pixelSize: Theme.fontSizeExtraSmall
                italic: true
            }
            horizontalAlignment: Text.AlignHCenter
        }

        ProgressCircle {
            id: progressIndicator
            width: Theme.iconSizeLarge
            height: Theme.iconSizeLarge
            anchors.centerIn: mediaButtonPause
            Timer {
                id: progressTimer
                property bool isRunning
                running: window.applicationActive && isRunning
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
            highlighted: true
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

    PushUpMenu {
        IconMenuItem {
            iconSource: "image://theme/icon-m-music"
            text: "Change quality/format"
            onClicked: openStreamsDialog()
        }
        IconMenuItem {
            iconSource: "qrc:/icon/un-bookmark"
            text: "Bookmark current song"
            onClicked: console.log("Bookmark current song")
        }
    }

    Connections {
        target: _player
        onChannelChanged: {
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
            channelId = _player.channelId()
        }
        onPlayCalled: open = true
        onPlayStarted: {
            reinitProgressIndicator()
            state = "playing"
        }
        onPauseStarted: {
            reinitProgressIndicator()
            state = "pause"
        }
        onNetworkError: showMessage("A network error occured")
    }

    Connections {
        target: _refreshModel
        onRefreshed: {
            var channel = _player.channel()
            if (!channel) return;
            var playing = _refreshModel.playing(channel)
            artist = playing.artist
            song = playing.song
        }
    }

    function reinitProgressIndicator() {
        progressIndicator.value = 0
        progressIndicator.inAlternateCycle = true
    }

    function goToChannelPage() {
        if (isDialogPage(pageStack.currentPage))
            return

        var url = Qt.resolvedUrl("../pages/ChannelPage.qml")
        var properties = {"id": channelId}

        var currentPage = pageStack.currentPage
        if (isChannelPage(currentPage)) {
            if (currentPage.id !== channelId) {
                currentPage.stopUpdates()
                pageStack.replace(url, properties)
            }
            return
        }

        var previousChannelPage = pageStack.find(isChannelPage)
        if (previousChannelPage) {
            pageStack.replaceAbove(pageStack.previousPage(previousChannelPage), url, properties)
            return
        }

        pageStack.push(url, properties)
    }

    function isChannelPage(page) {
        return page.objectName === "ChannelPage"
    }

    function isDialogPage(page) {
        return page.objectName === "StreamDialog"
    }

    function openStreamsDialog() {
        if (isDialogPage(pageStack.currentPage))
            return

        pageStack.push(Qt.resolvedUrl("../pages/StreamsDialog.qml"),
            {"channelId": channelId})
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
            PropertyChanges { target: progressTimer;     isRunning: false }
            PropertyChanges { target: channelLabel;      color: Theme.primaryColor}
        },
        State {
            name: "playing"
            PropertyChanges { target: mediaButtonPlay;   visible: false }
            PropertyChanges { target: mediaButtonPause;  visible: true }
            PropertyChanges { target: controlPanel;      open: true; restoreEntryValues: false }
            PropertyChanges { target: progressTimer;     isRunning: true }
            PropertyChanges { target: channelLabel;      color: Theme.highlightColor }
        }]

    onOpenChanged: {
        if (!open) {
            if (state === "playing")
                pause()
            close()
        }
    }
}
