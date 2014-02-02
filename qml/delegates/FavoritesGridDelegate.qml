/**
 *
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
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

        onPressAndHold: gridView.showContextMenu(itemcontainer)

        onClicked: _goToChannelPage()
    }

    function _goToChannelPage() {
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
