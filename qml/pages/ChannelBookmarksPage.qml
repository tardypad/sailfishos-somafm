import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"
import "../components"

Page {
    property string channelId

    SilicaListView {
        id: listView

        property var channelsData

        anchors.fill: parent
        header: IconPageHeader {
            title: "Song bookmarks"
            iconSource: "qrc:/icon/bookmark"
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
                iconSource: "qrc:/icon/un-bookmark"
                onClicked: removeAllBookmarks()
            }
        }

        ViewPlaceholder {
            enabled: listView.count === 0
            text: "No Bookmarks"
            hintText: "You can bookmark a song you loved or want to check later"
        }

        Component.onCompleted: {
            retrieveChannelData()
            _bookmarksManager.filterByChannel(channelId)
            _bookmarksManager.sortByDate()
        }

        function retrieveChannelData() {
            var tmpData = new Object();
            tmpData[channelId] = _bookmarksManager.channelData(channelId)
            channelsData = tmpData;
        }

        VerticalScrollDecorator { flickable: listView }
    }

    function removeAllBookmarks() {
        _bookmarksManager.removeAllChannelBookmarks(channelId)
    }

    SongPanel{
        id: songPanel
    }
}
