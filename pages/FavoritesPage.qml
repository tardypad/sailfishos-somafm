import QtQuick 2.0
import Sailfish.Silica 1.0

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
                nextPage: "GenresPage.qml"
                isReplace: true
            }
            IconPageMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                nextPage: "PopularsPage.qml"
                isReplace: true
            }
        }

        ViewPlaceholderHint {
            enabled: gridView.count === 0 && _favoritesManager.isEmpty()
            text: "No Favorites"
            hintText: "You can favorite a channel from the top menu of its page, or by 'tap and hold' on it in channels lists"
        }

        Component.onCompleted: {
            if (!_channelsModel.hasDataBeenFetchedOnce())
                _channelsModel.fetch();
        }

        VerticalScrollDecorator { flickable: gridView }
    }

    BusyIndicator {
        id: indicator
        size: BusyIndicatorSize.Large
        running: !_channelsModel.hasDataBeenFetchedOnce()
        anchors.centerIn: gridView
    }

    Connections {
        target: _channelsModel
        onDataFetched: indicator.running = false
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
