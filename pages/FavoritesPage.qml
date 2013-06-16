import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaGridView {
        id: gridView
        anchors.fill: parent
        header: ChannelsPageHeader {
            text: "Favorites"
            iconSource: "qrc:/icons/favorites"
        }
        model: channelsModel
        delegate: ChannelsFavoritesDelegate { }
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2

        PullDownMenu {
            ChannelsMenuItem {
                text: "Genres"
                iconSource: "qrc:/icons/genres"
                nextPage: "GenresPage.qml"
            }
            ChannelsMenuItem {
                text: "Populars"
                iconSource: "qrc:/icons/populars"
                nextPage: "PopularsPage.qml"
            }
        }

        Component.onCompleted: {
            channelsModel.hideClones()
            channelsModel.filterFavorites()
            channelsModel.sortByName()
        }

        VerticalScrollDecorator { flickable: gridView }
    }
}
