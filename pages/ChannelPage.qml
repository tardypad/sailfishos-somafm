import QtQuick 2.0
import Sailfish.Silica 1.0

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

        VerticalScrollDecorator { flickable: listView }
    }

    BusyIndicator {
        id: indicator
        size: BusyIndicatorSize.Large
        running: true
        anchors.centerIn: listView
    }

    Connections {
        target: _channelSongsModel
        onDataFetched: indicator.running = false
        onNetworkError: {
            indicator.running = false
            loader.sourceComponent = networkError
        }
    }

    Component {
        id: networkError
        ViewPlaceholder {
            enabled: true
            text: "Network error"
            hintText: "Can't download songs list"
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
}
