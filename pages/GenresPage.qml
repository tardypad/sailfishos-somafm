import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: PageHeader {
            title: "Genres"
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
            MenuItem {
                text: "Populars"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
            }
            MenuItem {
                text: "Favorites"
                onClicked: pageStack.replace(Qt.resolvedUrl("FavoritesPage.qml"))
            }
        }

        Component.onCompleted: {
            channelsModel.showClones(true)
            channelsModel.sortByGenres()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
