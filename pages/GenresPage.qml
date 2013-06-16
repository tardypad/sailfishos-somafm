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
        model: channelsModel
        delegate: ChannelsGenresDelegate { }
        section {
            property: 'sortGenre'
            delegate: SectionHeader {
                text: section
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
            channelsModel.clearFilter()
            channelsModel.showClones()
            channelsModel.sortByName()
            channelsModel.sortByGenres()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
