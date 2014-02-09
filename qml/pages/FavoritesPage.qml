/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"

Page {
    SilicaGridView {
        id: gridView

        // inspired from jolla-notes
        property Item contextMenu
        property int minOffsetIndex: contextMenu && contextMenu.parent
                                     ? contextMenu.parent.idx - (contextMenu.parent.idx % 2) + 2
                                     : 0

        anchors.fill: parent
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2
        header: IconPageHeader {
            title: "Favorites"
            iconSource: "favorite"
        }
        delegate: FavoritesGridDelegate { }

        PullDownMenu {
            IconMenuItem {
                text: "Genres"
                iconSource: "genre"
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
                inPullDown: true
            }
            IconMenuItem {
                text: "Populars"
                iconSource: "listener"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
                inPullDown: true
            }
        }

        function _showContextMenu(item) {
            if (!contextMenu)
                contextMenu = actionsComponent.createObject(gridView)
            contextMenu.show(item)
        }

        Component {
            id: actionsComponent
            ContextMenu {
                property Item delegate: parent
                property int index: delegate ? delegate.idx : -1
                property bool isPlaying: delegate ? _player.isPlaying(delegate.channelId) : false

                width: gridView.width

                IconMenuItem {
                    iconSource: !isPlaying ? "play" : "pause"
                    text: !isPlaying ? "Play" : "Pause"
                    onClicked: {
                        if (!isPlaying) {
                            gridView._play(index)
                        } else {
                            gridView._pause()
                        }
                    }
                }

                IconMenuItem {
                    iconSource: "unfavorite"
                    text: "Remove from favorites"
                    onClicked: gridView._removeFavorite(index)
                }
            }
        }

        ViewPlaceholder {
            enabled: gridView.count === 0 && indicator.state == "complete" &&_favoritesManager.isEmpty()
            text: "No Favorites"
            hintText: "You can favorite a channel to access it quicker"
        }

        LoadingIndicator {
            id: indicator
            model: _channelsModel
            flickable: gridView
            loadingText: "Loading channels list"
            defaultErrorText: "Can't display channels list"
            networkErrorText: "Can't download channels list"
            parsingErrorText: "Can't extract channels from list"
        }

        VerticalScrollDecorator { flickable: gridView }

        function _goToChannelPage(id) {
            pageStack.push(Qt.resolvedUrl("../pages/ChannelPage.qml"), {"id": id})
        }

        function _play(index) {
            _player.play(gridView.model.itemAt(index))
        }

        function _pause() {
            _player.pause()
        }

        function _removeFavorite(index) {
            _favoritesManager.removeFavorite(gridView.model.itemAt(index))
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
