import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: PageHeader {
            title: "Genres"
        }

        PullDownMenu {
            MenuItem {
                text: "Populars"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
            }
            MenuItem {
                text: "Favorites"
                onClicked: pageStack.replace(Qt.resolvedUrl("FavoritesPage.qml"))
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
