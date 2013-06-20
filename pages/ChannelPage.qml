import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
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
            MenuItem {
                text: !isFavorite ? "Add to Favorites" : "Remove from Favorites"
                onClicked: {
                    if (!isFavorite) {
                        _favoritesManager.addFavorite(id)
                        isFavorite = true
                    } else {
                        _favoritesManager.removeFavorite(id)
                        isFavorite = false
                    }
                }
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Component.onCompleted: {
        _channelSongsModel.setChannelId(id)
        _channelSongsModel.fetch()
    }
}
