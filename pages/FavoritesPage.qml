import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: PageHeader {
            title: "Favorites"
        }

        PullDownMenu {
            MenuItem {
                text: "Genres"
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
            }
            MenuItem {
                text: "Populars"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
