import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "Song bookmarks"
            iconSource: "qrc:/icons/bookmark"
        }

        ViewPlaceholderHint {
            enabled: listView.count === 0
            text: "No Bookmarks"
            hintText: "You can bookmark a song by 'tap and hold' on it"
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
