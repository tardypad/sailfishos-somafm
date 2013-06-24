import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: IconPageHeader {
            text: "News"
            iconSource: "qrc:/icons/news"
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
