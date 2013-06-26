import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Populars"
            iconSource: "qrc:/icon/popular"
        }
        model: _channelsModel
        delegate: PopularsDelegate { }
        property Item contextMenu

        PullDownMenu {
            IconPageMenuItem {
                text: "Genres"
                iconSource: "qrc:/icon/genre"
                nextPage: "GenresPage.qml"
                isReplace: true
            }
            IconPageMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icon/favorite"
                nextPage: "FavoritesPage.qml"
                isReplace: true
            }
        }

        Component {
            id: contextMenuComponent
            ContextMenu {
                property bool isFavorite
                property string id

                IconActionMenuItem {
                    iconSource: !isFavorite ? "qrc:/icon/favorite" : "qrc:/icon/un-favorite"
                    text: !isFavorite ? "Add to favorites" : "Remove from favorites"
                    onClicked: {
                        if (!isFavorite) {
                            _favoritesManager.addFavorite(id)
                        } else {
                            _favoritesManager.addFavorite(id)
                        }
                    }
                }
            }
        }

        Component.onCompleted: {
            _channelsModel.clearFilter()
            _channelsModel.hideClones()
            _channelsModel.sortByListeners()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
