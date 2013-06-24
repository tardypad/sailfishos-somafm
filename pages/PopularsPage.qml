import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Populars"
            iconSource: "qrc:/icons/populars"
        }
        model: _channelsModel
        delegate: PopularsDelegate { }

        PullDownMenu {
            IconPageMenuItem {
                text: "Genres"
                iconSource: "qrc:/icons/genres"
                nextPage: "GenresPage.qml"
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
            _channelsModel.hideClones()
            _channelsModel.sortByListeners()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
