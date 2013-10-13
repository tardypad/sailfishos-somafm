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
            IconMenuItem {
                text: "Genres"
                iconSource: "qrc:/icon/genre"
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
            }
            IconMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
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
        onDataFetched: stopLoadingAnimation()
        onNetworkError: {
            stopLoadingAnimation()
            displayError("Network error", "Can't download channels list")
        }
        onParsingError: {
            stopLoadingAnimation()
            displayError("Parsing error", "Can't extract channels from list")
        }
    }

    function displayError(text, hintText) {
        loader.sourceComponent = errorComponent
        if (typeof(text) != "undefined") loader.item.text = text
        if (typeof(hintText) != "undefined") loader.item.hintText = hintText
    }

    Component {
        id: errorComponent
        ViewPlaceholder {
            enabled: true
            text: "An error occured"
            hintText: "Can't display channels list"
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

    function stopLoadingAnimation() {
        indicator.running = false
    }
}
