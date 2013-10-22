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
            IconMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
            }
            IconMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icon/favorite"
                onClicked: pageStack.replace(Qt.resolvedUrl("FavoritesPage.qml"))
            }
        }

        LoadingIndicator {
            id: indicator
            running: !_channelsModel.hasDataBeenFetchedOnce()
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
            _channelsModel.showClones()
            _channelsModel.sortByName()
            _channelsModel.sortByGenres()
            listView.model = _channelsModel
        }
    }
}