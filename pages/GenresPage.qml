import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Genres"
            iconSource: "qrc:/icons/genres"
        }
        model: _channelsModel
        delegate: ChannelsDelegate { }
        section {
            property: 'sortGenre'
            delegate: SectionHeader {
                text: section
                height: implicitHeight + 2*theme.paddingMedium
                width: parent.width
            }
        }
        property Item contextMenu

        PullDownMenu {
            IconPageMenuItem {
                text: "Populars"
                iconSource: "qrc:/icons/populars"
                nextPage: "PopularsPage.qml"
                isReplace: true
            }
            IconPageMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icons/favorites"
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
                    iconSource: !isFavorite ? "qrc:/icons/favorites" : "qrc:/icons/un-favorite"
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
            _channelsModel.showClones()
            _channelsModel.sortByName()
            _channelsModel.sortByGenres()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
