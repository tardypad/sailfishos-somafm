import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
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

        ViewPlaceholderHint {
            enabled: listView.count === 0
            text: "No Bookmarks"
            hintText: "You can bookmark a song in a channel page by 'tap and hold' on it"
        }

        Component.onCompleted: {
            _bookmarksManager.sortByDate()
            _bookmarksManager.sortByChannel()
        }

        VerticalScrollDecorator { flickable: listView }
    }

    SongPanel{
        id: songPanel
    }
}
