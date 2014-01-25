import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"
import "../components"

Page {
    property Item _remorseItem

    SilicaListView {
        id: listView

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
