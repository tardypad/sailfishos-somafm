import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: PageHeader {
            title: "Popular Channels"
        }
        model: ChannelsModel { }
        delegate: ChannelsDelegate { }

        PullDownMenu {
            MenuItem {
                text: "Favorites"
                onClicked: pageStack.push(Qt.resolvedUrl("FavoritesPage.qml"))
            }
            MenuItem {
                text: "Genres"
                onClicked: pageStack.push(Qt.resolvedUrl("GenresPage.qml"))
            }
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
