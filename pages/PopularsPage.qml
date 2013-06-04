import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: PageHeader {
            title: "Populars"
        }
        model: ChannelsModel { }
        delegate: ChannelsDelegate { }

        PullDownMenu {
            MenuItem {
                text: "Genres"
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
            }
            MenuItem {
                text: "Favorites"
                onClicked: pageStack.replace(Qt.resolvedUrl("FavoritesPage.qml"))
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
