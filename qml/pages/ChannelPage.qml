import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"
import "components"

Page {
    property int channelIndex

    property string id
    property string name
    property string description
    property string dj
    property url imageUrl
    property url mediumImageUrl
    property url bigImageUrl
    property string genre
    property int listeners
    property bool isFavorite
    property bool isPlaying

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: ChannelPageHeader { }
        model: _channelSongsModel
        delegate: ChannelSongsDelegate { }

        PullDownMenu {
            IconMenuItem {
                text: "Song bookmarks"
                iconSource: "qrc:/icon/bookmark"
                onClicked: pageStack.push("ChannelBookmarksPage.qml", {"channelId": id})
            }
            IconMenuItem {
                iconSource: !isFavorite ? "qrc:/icon/favorite" : "qrc:/icon/un-favorite"
                text: !isFavorite ? "Add to Favorites" : "Remove from Favorites"
                onClicked: {
                    if (!isFavorite) {
                        addToFavorites()
                    } else {
                        removeFromFavorites()
                    }
                }
            }
            IconMenuItem {
                iconSource: !isPlaying ? "image://theme/icon-l-play" : "image://theme/icon-l-pause"
                text: !isPlaying ? "Play" : "Pause"
                onClicked: {
                    if (!isPlaying) {
                        play()
                    } else {
                        pause()
                    }
                }
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

    function play() {
        _player.play(_channelsModel.itemAt(channelIndex))
    }

    function pause() {
        _player.pause()
    }

    Connections {
        target: _player
        onPlayStarted: isPlaying = true
        onPauseStarted: isPlaying = false
    }

    function addToFavorites() {
        var result = _favoritesManager.addFavorite(_channelsModel.itemAt(channelIndex))
        if (result) isFavorite = true
    }

    function removeFromFavorites() {
        var result = _favoritesManager.removeFavorite(_channelsModel.itemAt(channelIndex))
        if (result) isFavorite = false
    }

    Component.onCompleted: {
        _channelSongsModel.setChannel(_channelsModel.itemAt(channelIndex))
        _channelSongsModel.fetch()
        isPlaying = _player.isPlaying(id)
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _channelSongsModel.abortFetching()
    }
}
