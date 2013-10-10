import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"

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
                nextPage: Qt.resolvedUrl("GenresPage.qml")
                isReplace: true
            }
            IconPageMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icon/favorite"
                nextPage: Qt.resolvedUrl("FavoritesPage.qml")
                isReplace: true
            }
        }

        Loader {
            id: loader
        }

        LoadingIndicator {
            id: indicator
            running: !_channelsModel.hasDataBeenFetchedOnce()
            flickable: listView
            text: "Loading channels list"
        }

        VerticalScrollDecorator { flickable: listView }
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
        if (status === PageStatus.Active && !listView.model) {
            _channelsModel.clearFilter()
            _channelsModel.hideClones()
            _channelsModel.sortByListeners()
            listView.model = _channelsModel
        }
    }

    function stopLoadingAnimation() {
        indicator.running = false
    }
}
