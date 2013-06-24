import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageMenuItem {
            text: "Genres"
            iconSource: "qrc:/icons/genres"
        }
        model: _channelsModel
        delegate: GenresDelegate { }
        section {
            property: 'sortGenre'
            delegate: SectionHeader {
                text: section
                height: implicitHeight + 2*theme.paddingMedium
                width: parent.width
            }
        }

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

        Component.onCompleted: {
            _channelsModel.clearFilter()
            _channelsModel.showClones()
            _channelsModel.sortByName()
            _channelsModel.sortByGenres()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
