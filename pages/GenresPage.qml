import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: ChannelsPageHeader {
            text: "Genres"
            iconSource: "qrc:/icons/genres"
        }
        model: _channelsModel
        delegate: GenresDelegate { }
        section {
            property: 'sortGenre'
            delegate: Item {
                width: parent.width
                height: sectionHeader.height * 1.5

                SectionHeader {
                    id: sectionHeader
                    text: section
                    anchors.bottom: parent.bottom
                }
            }
        }

        PullDownMenu {
            ChannelsMenuItem {
                text: "Populars"
                iconSource: "qrc:/icons/populars"
                nextPage: "PopularsPage.qml"
            }
            ChannelsMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icons/favorites"
                nextPage: "FavoritesPage.qml"
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
