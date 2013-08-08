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
        property Item contextMenu

        ViewPlaceholderHint {
            enabled: listView.count === 0
            text: "No Bookmarks"
            hintText: "You can bookmark a song by 'tap and hold' on it"
        }

        VerticalScrollDecorator { flickable: listView }
    }

    Component {
        id: contextMenuComponent
        ContextMenu {
            property int index

            IconActionMenuItem {
                iconSource: "qrc:/icon/un-bookmark"
                text: "Remove from bookmarks"
                onClicked: _bookmarksManager.removeBookmark(_bookmarksManager.itemAt(index))
            }
        }
    }
}
