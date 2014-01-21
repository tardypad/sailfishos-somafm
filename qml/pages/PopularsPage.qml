import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            title: "Populars"
            iconSource: somaTheme.getIconQrc("listener", "medium")
        }
        delegate: PopularsListDelegate { }

        PullDownMenu {
            IconMenuItem {
                text: "Genres"
                iconSource: somaTheme.getIconQrc("genre", "small")
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
                inPullDown: true
            }
            IconMenuItem {
                text: "Favorites"
                iconSource: somaTheme.getIconQrc("favorite", "small")
                onClicked: pageStack.replace(Qt.resolvedUrl("FavoritesPage.qml"))
                inPullDown: true
            }
        }

        LoadingIndicator {
            id: indicator
            model: _channelsModel
            flickable: listView
            loadingText: "Loading channels list"
            defaultErrorText: "Can't display channels list"
            networkErrorText: "Can't download channels list"
            parsingErrorText: "Can't extract channels from list"
        }

        VerticalScrollDecorator { flickable: listView }
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
