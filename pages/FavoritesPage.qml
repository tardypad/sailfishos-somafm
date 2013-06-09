import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaGridView {
        id: gridView
        anchors.fill: parent
        header: PageHeader {
            title: "Favorites"
        }
        model: channelsModel
        delegate: ChannelsFavoritesDelegate { }
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2

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

        VerticalScrollDecorator { flickable: gridView }
    }
}
