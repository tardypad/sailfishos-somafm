import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Genres"
            iconSource: "qrc:/icon/genre"
        }
        delegate: ChannelsDelegate { }
        section {
            property: 'sortGenre'
            delegate: SectionHeader {
                text: section
            }
        }

        PullDownMenu {
            IconPageMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                nextPage: Qt.resolvedUrl("PopularsPage.qml")
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
        onDataFetched: indicator.running = false
        onNetworkError: {
            indicator.running = false
            loader.sourceComponent = errorComponent
            loader.item.text = "Network error"
            loader.item.hintText = "Can't download channels list"
        }
        onParsingError: {
            indicator.running = false
            loader.sourceComponent = errorComponent
            loader.item.text = "Parsing error"
            loader.item.hintText = "Can't extract channels from list"
        }
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
            _channelsModel.showClones()
            _channelsModel.sortByName()
            _channelsModel.sortByGenres()
            listView.model = _channelsModel
        }
    }
}
