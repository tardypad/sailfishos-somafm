import QtQuick 1.1
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: listView
        anchors.fill: parent
        header: ChannelsPageHeader {
            text: "Populars"
            iconSource: "qrc:/icons/populars"
        }
        model: _channelsModel
        delegate: PopularsDelegate { }

        PullDownMenu {
            ChannelsMenuItem {
                text: "Genres"
                iconSource: "qrc:/icons/genres"
                nextPage: "GenresPage.qml"
            }
            ChannelsMenuItem {
                text: "Favorites"
                iconSource: "qrc:/icons/favorites"
                nextPage: "FavoritesPage.qml"
            }
        }

        Component.onCompleted: {
            _channelsModel.clearFilter()
            _channelsModel.hideClones()
            _channelsModel.sortByListeners()
        }

        VerticalScrollDecorator { flickable: listView }
    }
}
