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
import "../components"

import "../scripts/ExternalLinks.js" as ExternalLinks

Page {
    property Item _remorseItem

    SilicaListView {
        id: listView

        property alias contextMenu: contextMenu
        property var channelsData

        anchors.fill: parent
        header: IconPageHeader {
            title: "Song bookmarks"
            iconSource: "bookmark"
        }
        model: _bookmarksManager
        delegate: BookmarksListDelegate { }
        section {
            property: 'channelId'
            delegate: BookmarksSectionDelegate { }
        }

        PullDownMenu {
            IconMenuItem {
                text: "Remove all"
                iconSource: "unbookmark"
                onClicked: _removeAllBookmarks()
                inPullDown: true
            }
        }

        ViewPlaceholder {
            enabled: listView.count === 0
            text: "No Bookmarks"
            hintText: "You can bookmark a song you loved or want to check later"
        }

        Component {
            id: contextMenu
            ContextMenu {
                property Item delegate: parent
                property int index: delegate ? delegate.idx : -1
                property string artist: delegate ? delegate.artist_d : ""
                property string title: delegate ? delegate.title_d : ""

                IconMenuItem {
                    iconSource: "unbookmark"
                    text: "Remove from bookmarks"
                    onClicked: delegate.remove()
                }
                IconMenuItem {
                    iconSource: "google"
                    text: "Search on Google"
                    onClicked: ExternalLinks.searchGoogle([artist, title])
                }
            }
        }

        Component.onCompleted: {
            _retrieveChannelsData();
            _bookmarksManager.clearFilter()
            _bookmarksManager.sortByChannel()
        }

        function _retrieveChannelsData() {
            var tmpData = new Object();
            var channelIds = _bookmarksManager.channelIds()
            for (var i=0; i<channelIds.length; i++) {
                tmpData[channelIds[i]] = _bookmarksManager.channelData(channelIds[i])
            }
            channelsData = tmpData;
        }

        function _addChannelData(channelId) {
            channelsData[channelId] = _bookmarksManager.channelData(channelId)
        }

        function _removeBookmark(index) {
             _bookmarksManager.removeBookmark(listView.model.itemAt(index))
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Connections {
        target: _bookmarksManager
        onFirstChannelBookmark: listView._addChannelData(channelId)
    }

    function _removeAllBookmarks() {
        if (_remorseItem || !listView.count)
            return

        _remorseItem = remorsecomponent.createObject(listView)
        listView.interactive = false
        backNavigation = false
        songPanel.hide()

        _remorseItem.onCanceled.connect(_endRemorseAction)
        _remorseItem.onTriggered.connect(_endRemorseAction)

        _remorseItem.execute(listView.headerItem, "Removing all bookmarks", function() {
            _bookmarksManager.removeAllBookmarks()
        })
    }

    function _endRemorseAction() {
        backNavigation = true
        listView.interactive = true
        _remorseItem.destroy()
    }

    SongPanel{
        id: songPanel
    }

    Component {
        id: remorsecomponent
        RemorseItem { }
    }
}
