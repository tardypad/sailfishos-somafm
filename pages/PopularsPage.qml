import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Populars"
            iconSource: "qrc:/icon/popular"
        }
        delegate: PopularsDelegate { }

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

        Loader {
            id: loader
        }

        VerticalScrollDecorator { flickable: listView }
    }

    BusyIndicator {
        id: indicator
        size: BusyIndicatorSize.Large
        running: !_channelsModel.hasDataBeenFetchedOnce()
        anchors.centerIn: listView
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
        if (status === PageStatus.Active && !listView.model) {
            _channelsModel.clearFilter()
            _channelsModel.hideClones()
            _channelsModel.sortByListeners()
            listView.model = _channelsModel
        }
    }
}
