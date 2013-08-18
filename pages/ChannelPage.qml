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
        property Item contextMenu

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

        VerticalScrollDecorator { flickable: listView }
    }

    Component {
        id: contextMenuComponent
        ContextMenu {
            property bool isBookmark
            property int index

            IconActionMenuItem {
                iconSource: !isBookmark ? "qrc:/icon/bookmark" : "qrc:/icon/un-bookmark"
                text: !isBookmark ? "Add to bookmarks" : "Remove from bookmarks"
                onClicked: {
                    if (!isBookmark) {
                        _bookmarksManager.addBookmark(_channelSongsModel.itemAt(index))
                    } else {
                        _bookmarksManager.removeBookmark(_channelSongsModel.itemAt(index))
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        _channelSongsModel.setChannel(_channelsModel.itemAt(channelIndex))
        _channelSongsModel.fetch()
    }
}
