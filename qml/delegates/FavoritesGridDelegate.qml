/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

import QtQuick 2.0
import Sailfish.Silica 1.0

import "../utils"
import "../components"

Item {
    id: itemcontainer

    property int idx: index
    property string channelId: id

    property bool _hasContextMenu: gridView.contextMenu && gridView.contextMenu.parent === itemcontainer

    width: gridView.cellWidth
    height: _hasContextMenu
            ? gridView.cellHeight + gridView.contextMenu.height
            : gridView.cellHeight

    BackgroundItem {
        id: channelItem

        width: gridView.cellWidth
        height: gridView.cellHeight
        y: gridView.contextMenu && index >= gridView.minOffsetIndex
           ? gridView.contextMenu.height
           : 0

        highlighted: down || _hasContextMenu

        ChannelImage {
            id: channelImage
            size: BusyIndicatorSize.Medium
            width: gridView.cellWidth - Theme.paddingSmall*2
            height: gridView.cellHeight - Theme.paddingSmall*2
            source: imageMediumUrl
            anchors.centerIn: parent
        }

        onPressAndHold: gridView._showContextMenu(itemcontainer)

        onClicked: gridView._goToChannelPage(id)
    }
}
