/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0

Item {
    property string channelId
    property string channelName
    property url channelImageUrl
    property string artist
    property string title
    property bool isSongBookmark
    property bool isSleepTimerRunning
    property int sleepTimeRemaining

    state: "pause"

    Connections {
        target: _player
        onChannelChanged: {
            channelName = _player.channelName()
            channelImageUrl = _player.channelImageUrl()
            channelId = _player.channelId()
        }
        onSongChanged: {
            artist = _player.artist()
            title = _player.title()
            isSongBookmark = _bookmarksManager.isBookmark(_getCurrentSong())
        }
        onSleepTimerStarted: {
            sleepTimeRemaining = 0
            isSleepTimerRunning = true
        }
        onSleepTimerEnded: isSleepTimerRunning = false
        onPlayCalled: controlPanel.open = true
        onPlayStarted: state = "playing"
        onPauseStarted: state = "pause"
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
            if (isSongBookmark && channelId === control.channelId) {
                isSongBookmark = false
                showInfo("song removed from bookmarks")
            }
        }
    }

    function showErrorInfo(type, error) {
        showInfo("a "+type+" error occured: "+error+" error")
    }

    function showInfo(text) {
        if (controlPanel.open)
            showMessage(text)
    }

    function stopSleepTimer() {
        _player.stopSleepTimer();
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
        },
        State {
            name: "playing"
            PropertyChanges { target: controlPanel; open: true; restoreEntryValues: false }
        }]
}
