import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"

Page {
    SilicaGridView {
        id: gridView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Favorites"
            iconSource: "qrc:/icon/favorite"
        }
        delegate: FavoritesDelegate { }
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2

        PullDownMenu {
            IconPageMenuItem {
                text: "Genres"
                iconSource: "qrc:/icon/genre"
                nextPage: Qt.resolvedUrl("GenresPage.qml")
                isReplace: true
            }
            IconPageMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                nextPage: Qt.resolvedUrl("PopularsPage.qml")
                isReplace: true
            }
        }

        ViewPlaceholder {
            enabled: gridView.count === 0 && _favoritesManager.isEmpty()
            text: "No Favorites"
            hintText: "You can favorite a channel to access it quicker"
        }

        Loader {
            id: loader
        }

        LoadingIndicator {
            id: indicator
            running: !_channelsModel.hasDataBeenFetchedOnce()
            flickable: gridView
            text: "Loading channels list"
        }

        VerticalScrollDecorator { flickable: gridView }
    }

    Connections {
        target: _channelsModel
        onDataFetched: indicator.running = false
        onNetworkError: {
            indicator.running = false
            loader.sourceComponent = networkError
        }
    }

    Component {
        id: networkError
        ViewPlaceholder {
            enabled: true
            text: "Network error"
            hintText: "Can't download channels list"
        }
    }

    Component.onCompleted: {
        if (!_channelsModel.hasDataBeenFetchedOnce())
            _channelsModel.fetch();
    }

    onStatusChanged: {
        if (status === PageStatus.Active && !gridView.model) {
            _channelsModel.hideClones()
            _channelsModel.filterFavorites()
            _channelsModel.sortByBookmarkDate()
            gridView.model = _channelsModel
        }
    }
}
