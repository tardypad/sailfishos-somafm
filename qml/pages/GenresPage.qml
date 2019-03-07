/**
 * Copyright (c) 2013-2019 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"

Page {
    SilicaListView {
        id: listView

        property alias contextMenu: contextMenu

        anchors.fill: parent
        header: IconPageHeader {
            title: "Genres"
            iconSource: "genre"
        }
        delegate: ChannelsListDelegate { }
        section {
            property: 'sortGenre'
            delegate: SectionHeader {
                text: section
            }
        }

        PullDownMenu {
            IconMenuItem {
                text: "Populars"
                iconSource: "listener"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
                inPullDown: true
            }
            IconMenuItem {
                text: "Favorites"
                iconSource: "favorite"
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
            emptyText: "No channel to display"
        }

        Component {
            id: contextMenu
            ContextMenu {
                property Item delegate: parent
                property int index: delegate ? delegate.idx : -1
                property bool isFavorite: delegate ? delegate.isFavorite : false
                property bool isPlaying: delegate ? _player.isPlaying(delegate.channelId) : false

                IconMenuItem {
                    iconSource: !isPlaying ? "play" : "pause"
                    text: !isPlaying ? "Play" : "Pause"
                    onClicked: {
                        if (!isPlaying) {
                            listView._play(index)
                        } else {
                            listView._pause()
                        }
                    }
                }

                IconMenuItem {
                    iconSource: !isFavorite ? "favorite" : "unfavorite"
                    text: !isFavorite ? "Add to favorites" : "Remove from favorites"
                    onClicked: {
                        if (!isFavorite) {
                            listView._addFavorite(index)
                        } else {
                            listView._removeFavorite(index)
                        }
                    }
                }
            }
        }

        function _goToChannelPage(id) {
            pageStack.push(Qt.resolvedUrl("../pages/ChannelPage.qml"), {"id": id})
        }

        function _play(index) {
            _player.play(listView.model.itemAt(index))
        }

        function _pause() {
            _player.pause()
        }

        function _addFavorite(index) {
            _favoritesManager.addFavorite(listView.model.itemAt(index))
        }

        function _removeFavorite(index) {
            _favoritesManager.removeFavorite(listView.model.itemAt(index))
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Component.onCompleted: {
        if (!_channelsModel.hasDataBeenFetchedOnce())
            _channelsModel.fetch()
        else
            indicator.complete()
    }

    onStatusChanged: {
        if (status === PageStatus.Active && !listView.model) {
            _channelsModel.clearFilter()
            _channelsModel.showClones()
            _channelsModel.sortByGenres()
            listView.model = _channelsModel
        }
    }
}
