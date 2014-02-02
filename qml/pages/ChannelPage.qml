/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 **/


import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"
import "../components"

Page {
    id: channelPage
    objectName: "ChannelPage"

    property string id

    property string _name
    property string _description
    property string _dj
    property string _djMail
    property url _imageUrl
    property url _mediumImageUrl
    property url _bigImageUrl
    property int _listeners
    property bool _isFavorite
    property bool _isPlaying

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: ChannelPageHeader { }
        model: _channelSongsModel
        delegate: ChannelSongsListDelegate { }

        PullDownMenu {
            id: pulleyMenu

            IconMenuItem {
                text: "Song bookmarks"
                iconSource: "bookmark"
                onClicked: pageStack.push("ChannelBookmarksPage.qml", {"channelId": id})
                inPullDown: true
            }
            IconMenuItem {
                iconSource: !_isFavorite ? "favorite" : "unfavorite"
                text: !_isFavorite ? "Add to Favorites" : "Remove from Favorites"
                onClicked: {
                    if (!_isFavorite) {
                        _addToFavorites()
                    } else {
                        _removeFromFavorites()
                    }
                }
                inPullDown: true
            }
            IconMenuItem {
                iconSource: !_isPlaying ? "play" : "pause"
                text: !_isPlaying ? "Play" : "Pause"
                onClicked: {
                    if (!_isPlaying) {
                        play()
                    } else {
                        _pause()
                    }
                }
                inPullDown: true
            }
        }

        LoadingIndicator {
            id: indicator
            model: _channelSongsModel
            flickable: listView
            loadingText: "Loading songs list"
            defaultErrorText: "Can't display songs list"
            networkErrorText: "Can't download songs list"
            parsingErrorText: "Can't extract songs from list"
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Connections {
        target: window
        onApplicationActiveChanged: {
            if (window.applicationActive) {
                _fetchNewSongs()
            }
        }
    }

    function _getChannelItem() {
        return _channelsModel.channelItem(id)
    }

    function _initData() {
        var channelData = _channelsModel.channelItemNameData(id)
        _name = channelData.name
        _description = channelData.description
        _dj = channelData.dj
        _djMail = channelData.djMail
        _imageUrl = channelData.imageUrl
        _mediumImageUrl = channelData.imageMediumUrl
        _bigImageUrl = channelData.imageBigUrl
        _listeners = channelData.listeners
        _isFavorite = channelData.isBookmark
    }

    function play() {
        _player.play(_getChannelItem())
    }

    function _pause() {
        _player.pause()
    }

    Connections {
        target: _player
        onPlayStarted: _isPlaying = _player.isPlaying(id)
        onPauseStarted: _isPlaying = false
        onSongChanged: {
            if (window.applicationActive)
                _fetchNewSongs()
        }
    }

    function _addToFavorites() {
        var result = _favoritesManager.addFavorite(_getChannelItem())
        if (result) _isFavorite = true
    }

    function _removeFromFavorites() {
        var result = _favoritesManager.removeFavorite(_getChannelItem())
        if (result) _isFavorite = false
    }

    function stopUpdates() {
        indicator.stopped = true
        listView.model = null
    }

    Connections {
        target: _channelSongsModel
        onFetchUpdateStarted: pulleyMenu.busy = true
        onFetchUpdateFinished: pulleyMenu.busy = false
    }

    function _fetchNewSongs() {
        _channelSongsModel.fetchAdditional()
    }

    Component.onCompleted: {
        _initData()
        _channelSongsModel.setChannel(_getChannelItem())
        _channelSongsModel.fetch()
        _channelSongsModel.sortByDate()
        _isPlaying = _player.isPlaying(id)
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _channelSongsModel.abortFetching()
    }
}
