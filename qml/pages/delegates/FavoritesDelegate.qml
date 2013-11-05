import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"

BackgroundItem {
    id: channelItem

    property Item _contextMenu

    width: gridView.cellWidth
    height: gridView.cellHeight

    Image {
        id: channelImage
        width: gridView.cellWidth - Theme.paddingSmall*2
        height: gridView.cellHeight - Theme.paddingSmall*2
        sourceSize {
            width: gridView.cellWidth - Theme.paddingSmall*2
            height: gridView.cellHeight - Theme.paddingSmall*2
        }
        smooth: true
        source: (imageMediumUrl != "") ? imageMediumUrl : imageBigUrl
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        fillMode: Image.PreserveAspectCrop
        clip: true

        BusyIndicator {
            size: BusyIndicatorSize.Medium
            running: channelImage.status === Image.Loading
            anchors.centerIn: parent
        }
    }

    onPressAndHold: {
        if (rectLoader.status === Loader.Null)
            rectLoader.sourceComponent = rectComponent
        if (!_contextMenu)
            _contextMenu = actionsComponent.createObject(gridView)
        _contextMenu.isPlaying = _player.isPlaying(id)
        _contextMenu.show(channelItem)
    }

    onClicked: goToChannelPage()

    Loader {
        id: rectLoader
        anchors.fill: channelImage
        visible: _contextMenu ? _contextMenu.visible : false
    }

    Component {
        id: rectComponent
        Rectangle {
            color: "black"
            opacity: 0.8
        }
    }

    Component {
        id: actionsComponent
        ContextMenu {
            id: gridContextMenu

            property bool isPlaying
            visible: active

            width: gridView.cellWidth
            height: gridView.cellHeight
            x: channelImage.x - Theme.paddingSmall

            IconMenuItem {
                iconSource: !isPlaying ? "image://theme/icon-l-play" : "image://theme/icon-l-pause"
                text: !isPlaying ? "Play" : "Pause"
                height: gridView.cellHeight / 2
                onClicked: {
                    if (!isPlaying) {
                        play()
                    } else {
                        pause()
                    }
                }
            }

            IconMenuItem {
                iconSource: "qrc:/icon/un-favorite"
                height: gridView.cellHeight / 2
                text: "Remove"
                onClicked: removeFavorite()
            }
        }
    }

    function goToChannelPage() {
        pageStack.push(Qt.resolvedUrl("../ChannelPage.qml"), {"channelIndex": index})
    }

    function play() {
        _player.play(gridView.model.itemAt(index))
    }

    function pause() {
        _player.pause()
    }

    function removeFavorite() {
        _contextMenu.hide();
        _favoritesManager.removeFavorite(gridView.model.itemAt(index))
    }
}
