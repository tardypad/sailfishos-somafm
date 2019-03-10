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
    SilicaGridView {
        id: gridView

        // inspired from jolla-notes
        property Item contextMenu
        property int minOffsetIndex: contextMenu && contextMenu.parent
                                     ? contextMenu.parent.idx - (contextMenu.parent.idx % 2) + 2
                                     : 0
        property bool contextMenuActive: contextMenu && contextMenu.active

        anchors.fill: parent
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2
        header: IconPageHeader {
            title: "Favorites"
            iconSource: "favorite"
        }
        delegate: FavoritesGridDelegate { }

        // inspired from jolla-gallery
        Rectangle {
            property bool active: gridView.currentItem && gridView.currentItem.down && !gridView.contextMenuActive
            width: gridView.cellWidth
            height: gridView.cellHeight
            color: Theme.highlightBackgroundColor
            opacity: active ? 0.5 : 0
            x: gridView.currentItem != null ? gridView.currentItem.x : 0
            y: gridView.currentItem != null ? gridView.currentItem.y - gridView.contentY : 0
            z: gridView.currentItem != null ? gridView.currentItem.z + 1 : 0
        }

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

        PushUpMenu {
            IconMenuItem {
                text: "News"
                iconSource: "news"
                onClicked: pageStack.push(Qt.resolvedUrl("NewsPage.qml"))
            }
            IconMenuItem {
                text: "Song bookmarks"
                iconSource: "bookmark"
                onClicked: pageStack.push(Qt.resolvedUrl("BookmarksPage.qml"))
            }
            IconMenuItem {
                text: "Settings"
                iconSource: "settings"
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
            IconMenuItem {
                text: "About"
                iconSource: "about"
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        function _showContextMenu(item) {
            if (!contextMenu)
                contextMenu = actionsComponent.createObject(gridView)
            contextMenu.open(item)
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

        LoadingIndicator {
            id: indicator
            model: _channelsModel
            flickable: gridView
            loadingText: "Loading channels list"
            defaultErrorText: "Can't display channels list"
            networkErrorText: "Can't download channels list"
            parsingErrorText: "Can't extract channels from list"
            emptyText: "No favorites"
            emptyHintText: "You can favorite a channel to access it quicker"
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

        Connections {
            target: _favoritesManager
            onBookmarkAdded: indicator.removePlaceholder()
            onBookmarkRemoved: {
                if (_favoritesManager.isEmpty()) {
                    indicator.forceEmptyPlaceHolder()
                }
            }
        }
    }

    Component.onCompleted: {
        if (!_channelsModel.hasDataBeenFetchedOnce())
            _channelsModel.fetch()
        else {
            indicator.complete()
            if (_favoritesManager.isEmpty()) {
                indicator.forceEmptyPlaceHolder()
            }
        }
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
