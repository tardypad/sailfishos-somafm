import QtQuick 2.0
import Sailfish.Silica 1.0

import "utils"
import "delegates"
import "components"

Page {
    property string channelId

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Song bookmarks"
            iconSource: "qrc:/icon/bookmark"
        }
        model: _bookmarksManager
        delegate: BookmarksDelegate { }
        section {
            property: 'channelName'
            delegate: SectionHeader {
                text: section
            }
        }

        ViewPlaceholder {
            enabled: listView.count === 0
            text: "No Bookmarks"
            hintText: "You can bookmark a song you loved or want to check later"
        }

        Component.onCompleted: {
            _bookmarksManager.filterByChannel(channelId)
            _bookmarksManager.sortByDate()
        }

        VerticalScrollDecorator { flickable: listView }
    }

    SongPanel{
        id: songPanel
    }
}
