import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Genres"
            iconSource: "qrc:/icon/genre"
        }
        model: _channelsModel
        delegate: ChannelsDelegate { }
        section {
            property: 'sortGenre'
            delegate: SectionHeader {
                text: section
            }
        }

        PullDownMenu {
            IconPageMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                nextPage: "PopularsPage.qml"
                isReplace: true
            }
            IconPageMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icon/favorite"
                nextPage: "FavoritesPage.qml"
                isReplace: true
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
