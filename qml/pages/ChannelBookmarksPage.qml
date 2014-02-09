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
import "../components"

import "../scripts/ExternalLinks.js" as ExternalLinks

Page {
    id: page

    property string channelId
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
            _retrieveChannelData()
            _bookmarksManager.filterByChannel(channelId)
            _bookmarksManager.sortByDate()
        }

        function _retrieveChannelData() {
            var tmpData = new Object();
            tmpData[channelId] = _bookmarksManager.channelData(channelId)
            channelsData = tmpData;
        }

        function _removeBookmark(index) {
             _bookmarksManager.removeBookmark(listView.model.itemAt(index))
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Connections {
        target: _bookmarksManager
        onFirstChannelBookmark: {
            if (channelId === page.channelId)
                listView._retrieveChannelData()
        }
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
            _bookmarksManager.removeAllChannelBookmarks(channelId)
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
