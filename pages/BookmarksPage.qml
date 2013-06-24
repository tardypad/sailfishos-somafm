import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageMenuItem {
            text: "Song bookmarks"
            iconSource: "qrc:/icons/bookmark"
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
