/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
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
            title: "Populars"
            iconSource: "listener"
        }
        delegate: PopularsListDelegate { }

        PullDownMenu {
            IconMenuItem {
                text: "Genres"
                iconSource: "genre"
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
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
