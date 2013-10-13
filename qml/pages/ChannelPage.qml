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
            IconActionMenuItem {
                text: "Song bookmarks"
                iconSource: "qrc:/icon/bookmark"
                onClicked: pageStack.push("ChannelBookmarksPage.qml", {"channelId": id})
            }
            IconActionMenuItem {
                iconSource: !isFavorite ? "qrc:/icon/favorite" : "qrc:/icon/un-favorite"
                text: !isFavorite ? "Add to Favorites" : "Remove from Favorites"
                onClicked: {
                    if (!isFavorite) {
                        _favoritesManager.addFavorite(_channelsModel.itemAt(channelIndex))
                        isFavorite = true
                    } else {
                        _favoritesManager.removeFavorite(_channelsModel.itemAt(channelIndex))
                        isFavorite = false
                    }
                }
            }
        }

        Loader {
            id: loader
        }

        LoadingIndicator {
            id: indicator
            running: true
            flickable: listView
            text: "Loading songs list"
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Connections {
        target: _channelSongsModel
        onDataFetched: stopLoadingAnimation()
        onNetworkError: {
            stopLoadingAnimation()
            displayError("Network error", "Can't download songs list")
        }
        onParsingError: {
            stopLoadingAnimation()
            displayError("Parsing error", "Can't extract songs from list")
        }
    }

    function displayError(text, hintText) {
        loader.sourceComponent = errorComponent
        if (typeof(text) != "undefined") loader.item.text = text
        if (typeof(hintText) != "undefined") loader.item.hintText = hintText
    }

    Component {
        id: errorComponent
        ViewPlaceholder {
            enabled: true
            text: "An error occured"
            hintText: "Can't display songs list"
        }
    }

    Component.onCompleted: {
        _channelSongsModel.setChannel(_channelsModel.itemAt(channelIndex))
        _channelSongsModel.fetch()
    }

    onStatusChanged: {
        if (status === PageStatus.Inactive)
            _channelSongsModel.abortFetching()
    }

    function stopLoadingAnimation() {
        indicator.running = false
    }
}
