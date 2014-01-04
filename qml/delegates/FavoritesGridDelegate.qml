import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../components"

Item {
    id: itemcontainer

    property int idx: index
    property string channelId: id
    property bool hasContextMenu: gridView.contextMenu && gridView.contextMenu.parent === itemcontainer

    width: gridView.cellWidth
    height: hasContextMenu
            ? gridView.cellHeight + gridView.contextMenu.height
            : gridView.cellHeight

    BackgroundItem {
        id: channelItem

        width: gridView.cellWidth
        height: gridView.cellHeight
        y: gridView.contextMenu && index >= gridView.minOffsetIndex
           ? gridView.contextMenu.height
           : 0

        highlighted: down || hasContextMenu

        ChannelImage {
            id: channelImage
            size: BusyIndicatorSize.Medium
            width: gridView.cellWidth - Theme.paddingSmall*2
            height: gridView.cellHeight - Theme.paddingSmall*2
            source: imageMediumUrl
            anchors.centerIn: parent
        }

        onPressAndHold: gridView.showContextMenu(itemcontainer)

        onClicked: goToChannelPage()
    }

    function goToChannelPage() {
        pageStack.push(Qt.resolvedUrl("../pages/ChannelPage.qml"), {"id": id})
    }

    function play() {
        _player.play(gridView.model.itemAt(index))
    }

    function pause() {
        _player.pause()
    }

    function removeFavorite() {
        _favoritesManager.removeFavorite(gridView.model.itemAt(index))
    }
}
