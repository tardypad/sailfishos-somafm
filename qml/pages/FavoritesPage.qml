import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../delegates"

Page {
    SilicaGridView {
        id: gridView

        // inspired from jolla-notes
        property Item contextMenu
        property int minOffsetIndex: contextMenu && contextMenu.parent
                                     ? contextMenu.parent.idx - (contextMenu.parent.idx % 2) + 2
                                     : 0

        anchors.fill: parent
        cellWidth: parent.width / 2
        cellHeight: parent.width / 2
        header: IconPageHeader {
            title: "Favorites"
            iconSource: "qrc:/icon/favorite"
        }
        delegate: FavoritesGridDelegate { }

        PullDownMenu {
            IconMenuItem {
                text: "Genres"
                iconSource: "qrc:/icon/genre"
                onClicked: pageStack.replace(Qt.resolvedUrl("GenresPage.qml"))
            }
            IconMenuItem {
                text: "Populars"
                iconSource: "qrc:/icon/popular"
                onClicked: pageStack.replace(Qt.resolvedUrl("PopularsPage.qml"))
            }
        }

        function showContextMenu(item) {
            if (!contextMenu)
                contextMenu = actionsComponent.createObject(gridView)
            contextMenu.isPlaying = _player.isPlaying(item.channelId)
            contextMenu.show(item)
        }

        Component {
            id: actionsComponent
            ContextMenu {
                id: gridContextMenu

                property bool isPlaying

                width: gridView.width

                IconMenuItem {
                    iconSource: !isPlaying ? "image://theme/icon-l-play" : "image://theme/icon-l-pause"
                    text: !isPlaying ? "Play" : "Pause"
                    onClicked: {
                        if (!isPlaying) {
                            gridContextMenu.parent.play()
                        } else {
                            gridContextMenu.parent.pause()
                        }
                    }
                }

                IconMenuItem {
                    iconSource: "qrc:/icon/un-favorite"
                    text: "Remove from favorites"
                    onClicked: gridContextMenu.parent.removeFavorite()
                }
            }
        }

        ViewPlaceholder {
            enabled: gridView.count === 0 && indicator.state == "complete" &&_favoritesManager.isEmpty()
            text: "No Favorites"
            hintText: "You can favorite a channel to access it quicker"
        }

        LoadingIndicator {
            id: indicator
            model: _channelsModel
            flickable: gridView
            loadingText: "Loading channels list"
            defaultErrorText: "Can't display channels list"
            networkErrorText: "Can't download channels list"
            parsingErrorText: "Can't extract channels from list"
        }

        VerticalScrollDecorator { flickable: gridView }
    }

    Component.onCompleted: {
        if (!_channelsModel.hasDataBeenFetchedOnce())
            _channelsModel.fetch();
    }

    onStatusChanged: {
        if (status === PageStatus.Active && !gridView.model) {
            _channelsModel.hideClones()
            _channelsModel.filterFavorites()
            _channelsModel.sortByBookmarkDate()
            gridView.model = _channelsModel
        }
    }
}
