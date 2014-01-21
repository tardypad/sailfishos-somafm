import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"
import "../components"

Page {
    id: channelPage
    objectName: "ChannelPage"

    property string id
    property string name
    property string description
    property string dj
    property string djMail
    property url imageUrl
    property url mediumImageUrl
    property url bigImageUrl
    property int listeners
    property bool isFavorite
    property bool isPlaying

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
                iconSource: somaTheme.getIconSource("bookmark", "small")
                onClicked: pageStack.push("ChannelBookmarksPage.qml", {"channelId": id})
                inPullDown: true
            }
            IconMenuItem {
                iconSource: !isFavorite ? somaTheme.getIconSource("favorite", "small") : somaTheme.getIconSource("unfavorite", "small")
                text: !isFavorite ? "Add to Favorites" : "Remove from Favorites"
                onClicked: {
                    if (!isFavorite) {
                        addToFavorites()
                    } else {
                        removeFromFavorites()
                    }
                }
                inPullDown: true
            }
            IconMenuItem {
                iconSource: !isPlaying ? somaTheme.getIconSource("play", "small") : somaTheme.getIconSource("pause", "small")
                text: !isPlaying ? "Play" : "Pause"
                onClicked: {
                    if (!isPlaying) {
                        play()
                    } else {
                        pause()
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

    Timer {
        id: reloadTimer
        running: window.applicationActive
        interval: 60000
        repeat: true
        onTriggered: fetchNewSongs()
    }

    Connections {
        target: window
        onApplicationActiveChanged: {
            if (window.applicationActive) {
                fetchNewSongs()
            }
        }
    }

    function getChannelItem() {
        return _channelsModel.channelItem(id)
    }

    function initData() {
        var channelData = _channelsModel.channelItemNameData(id)
        name = channelData.name
        description = channelData.description
        dj = channelData.dj
        djMail = channelData.djMail
        imageUrl = channelData.imageUrl
        mediumImageUrl = channelData.imageMediumUrl
        bigImageUrl = channelData.imageBigUrl
        listeners = channelData.listeners
        isFavorite = channelData.isBookmark
    }

    function play() {
        _player.play(getChannelItem())
    }

    function pause() {
        _player.pause()
    }

    Connections {
        target: _player
        onPlayStarted: isPlaying = _player.isPlaying(id)
        onPauseStarted: isPlaying = false
    }

    function addToFavorites() {
        var result = _favoritesManager.addFavorite(getChannelItem())
        if (result) isFavorite = true
    }

    function removeFromFavorites() {
        var result = _favoritesManager.removeFavorite(getChannelItem())
        if (result) isFavorite = false
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

    function fetchNewSongs() {
        _channelSongsModel.fetchAdditional()
    }

    Component.onCompleted: {
        initData()
        _channelSongsModel.setChannel(getChannelItem())
        _channelSongsModel.fetch()
        _channelSongsModel.sortByDate()
        isPlaying = _player.isPlaying(id)
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _channelSongsModel.abortFetching()
    }
}
