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
                text: "Play"
                iconSource: "image://theme/icon-l-play"
                onClicked: play()
            }
        }

        LoadingIndicator {
            id: indicator
            running: true
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

    function addToFavorites() {
        _favoritesManager.addFavorite(_channelsModel.itemAt(channelIndex))
        isFavorite = true
    }

    function removeFromFavorites() {
        _favoritesManager.removeFavorite(_channelsModel.itemAt(channelIndex))
        isFavorite = false
    }

    Component.onCompleted: {
        _channelSongsModel.setChannel(_channelsModel.itemAt(channelIndex))
        _channelSongsModel.fetch()
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _channelSongsModel.abortFetching()
    }
}
