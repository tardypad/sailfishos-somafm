/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

DockedPanel {
    id: controlPanel

    property alias isPushMenuActive: pushUpMenu.active

    property string channelId
    property alias channelName: channelLabel.text
    property alias channelImageUrl: channelImage.source
    property url channelImageMediumUrl
    property alias artist: artistLabel.text
    property alias title: titleLabel.text
    property bool isSongBookmark

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
            height: parent.height
            width: height
            anchors {
                left: parent.left
                top: parent.top
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
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }

        Label {
            id: artistLabel
            anchors {
                left: channelImage.right
                leftMargin: Theme.paddingMedium
                right: mediaButtonPause.left
                rightMargin: Theme.paddingMedium
                bottom: titleLabel.top
                bottomMargin: -Theme.paddingSmall
            }
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeExtraSmall
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
        }

        Label {
            id: titleLabel
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
            horizontalAlignment: implicitWidth < width ? Text.AlignHCenter : Text.AlignLeft
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
            icon.width: Theme.iconSizeMedium
            icon.height: Theme.iconSizeMedium
            anchors {
                right: parent.right
                rightMargin: Theme.paddingLarge
                verticalCenter: parent.verticalCenter
            }
            icon.asynchronous: true
            icon.source: somaTheme.getIconSource("pause", "medium")
            highlighted: true
            onClicked: pause()
        }

        IconButton {
            id: mediaButtonPlay
            icon.width: Theme.iconSizeMedium
            icon.height: Theme.iconSizeMedium
            anchors {
                right: parent.right
                rightMargin: Theme.paddingLarge
                verticalCenter: parent.verticalCenter
            }
            icon.asynchronous: true
            icon.source: somaTheme.getIconSource("play", "medium")
            onClicked: play()
        }

        onClicked: _goToChannelPage()
    }

    PushUpMenu {
        id: pushUpMenu
        IconMenuItem {
            iconSource: "stream"
            text: "Change channel quality/format"
            onClicked: _openStreamsDialog()
        }
        IconMenuItem {
            iconSource: !isSongBookmark ? "bookmark" : "unbookmark"
            text: !isSongBookmark ? "Add song to bookmarks" : "Remove song from bookmarks"
            onClicked: {
                if (!isSongBookmark) {
                    addSongToBookmarks()
                } else {
                    removeSongFromBookmarks()
                }
            }
        }
    }

    Connections {
        target: _player
        onChannelChanged: {
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
            channelImageMediumUrl = _player.channelImageMediumUrl()
            channelId = _player.channelId()
        }
        onSongChanged: {
            artist = _player.artist()
            title = _player.title()
            isSongBookmark = _bookmarksManager.isBookmark(_getCurrentSong())
        }
        onPlayCalled: open = true
        onPlayStarted: {
            _reinitProgressIndicator()
            state = "playing"
        }
        onPauseStarted: {
            _reinitProgressIndicator()
            state = "pause"
        }
        onMediaLoading: {
            if (state === "playing")
                progressTimer.stop()
        }
        onMediaLoaded: {
            if (state === "playing")
                progressTimer.start()
        }
        onPlaylistError: showErrorInfo("playlist", error)
        onMediaError: showErrorInfo("media", error)
    }

    Connections {
        target: _bookmarksManager
        onBookmarkAdded: {
            if (_isCurrentSong(xmlItem)) {
                isSongBookmark = true
                showInfo("song added to bookmarks")
            }
        }
        onBookmarkRemoved: {
            if (_isCurrentSong(xmlItem)) {
                isSongBookmark = false
                showInfo("song removed from bookmarks")
            }
        }
        onAllBookmarksRemoved: {
            if (isSongBookmark) {
                isSongBookmark = false
                showInfo("song removed from bookmarks")
            }
        }
        onAllChannelBookmarksRemoved: {
            if (isSongBookmark && channelId === controlPanel.channelId) {
                isSongBookmark = false
                showInfo("song removed from bookmarks")
            }
        }
    }

    function showErrorInfo(type, error) {
        showInfo("a "+type+" error occured: "+error+" error")
    }

    function showInfo(text) {
        if (open)
            showMessage(text)
    }

    function _reinitProgressIndicator() {
        progressIndicator.value = 0
        progressIndicator.inAlternateCycle = true
    }

    function _goToChannelPage() {
        if (_isDialogPage(pageStack.currentPage))
            return

        var url = Qt.resolvedUrl("../pages/ChannelPage.qml")
        var properties = {"id": channelId}

        var currentPage = pageStack.currentPage
        if (_isChannelPage(currentPage)) {
            if (currentPage.id !== channelId) {
                currentPage.stopUpdates()
                pageStack.replace(url, properties)
            }
            return
        }

        var previousChannelPage = pageStack.find(_isChannelPage)
        if (previousChannelPage) {
            pageStack.replaceAbove(pageStack.previousPage(previousChannelPage), url, properties)
            return
        }

        pageStack.push(url, properties)
    }

    function _isChannelPage(page) {
        return page.objectName === "ChannelPage"
    }

    function _isDialogPage(page) {
        return page.objectName === "StreamDialog"
    }

    function _openStreamsDialog() {
        if (_isDialogPage(pageStack.currentPage))
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

    function _isCurrentSong(song) {
        return _bookmarksManager.areEquals(song, _getCurrentSong())
    }

    function _getCurrentSong() {
        return _player.currentSong()
    }

    function addSongToBookmarks() {
        var result = _bookmarksManager.addBookmark(_getCurrentSong())
        if (result) isSongBookmark = true
    }

    function removeSongFromBookmarks() {
        var result = _bookmarksManager.removeBookmark(_getCurrentSong())
        if (result) isSongBookmark = false
    }

    states: [
        State {
            name: "pause"
            PropertyChanges { target: mediaButtonPlay;   visible: true }
            PropertyChanges { target: mediaButtonPause;  visible: false }
            PropertyChanges { target: progressTimer;     isRunning: false }
            PropertyChanges { target: channelLabel;      color: Theme.primaryColor}
            PropertyChanges { target: artistLabel;       color: Theme.primaryColor}
            PropertyChanges { target: titleLabel;        color: Theme.primaryColor}
        },
        State {
            name: "playing"
            PropertyChanges { target: mediaButtonPlay;   visible: false }
            PropertyChanges { target: mediaButtonPause;  visible: true }
            PropertyChanges { target: controlPanel;      open: true; restoreEntryValues: false }
            PropertyChanges { target: progressTimer;     isRunning: true }
            PropertyChanges { target: channelLabel;      color: Theme.highlightColor }
            PropertyChanges { target: artistLabel;       color: Theme.highlightColor }
            PropertyChanges { target: titleLabel;        color: Theme.highlightColor }
        }]

    onOpenChanged: {
        if (!open) {
            if (state === "playing")
                pause()
            close()
        }
    }
}
