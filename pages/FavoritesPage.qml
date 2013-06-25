import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaGridView {
        id: gridView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Favorites"
            iconSource: "qrc:/icons/favorites"
        }
        model: _channelsModel
        delegate: FavoritesDelegate { }
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2

        PullDownMenu {
            IconPageMenuItem {
                text: "Genres"
                iconSource: "qrc:/icons/genres"
                nextPage: "GenresPage.qml"
                isReplace: true
            }
            IconPageMenuItem {
                text: "Populars"
                iconSource: "qrc:/icons/populars"
                nextPage: "PopularsPage.qml"
                isReplace: true
            }
        }

        ViewPlaceholderHint {
            enabled: gridView.count === 0
            text: "No Favorites"
            hintText: "You can favorite a channel from the top menu of its page"
        }

        Component.onCompleted: {
            _channelsModel.hideClones()
            _channelsModel.filterFavorites()
            _channelsModel.sortByName()
        }

        VerticalScrollDecorator { flickable: gridView }
    }

    onStatusChanged: {
        if (status == PageStatus.Active) {
            _channelsModel.filterFavorites()
        }
    }
}
