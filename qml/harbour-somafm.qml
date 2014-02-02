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

import "pages"
import "cover"
import "components"
import "utils"

ApplicationWindow
{
    id: window

    initialPage: Component { HomePage { } }
    cover: DefaultCover { }
    bottomMargin: controlPanel.visibleSize

    Loader {
        id: messageLoader
        anchors.bottom: controlPanel.top
        visible: !controlPanel.isPushMenuActive
        onVisibleChanged: {
            if (!visible)
                hideMessage()
        }
    }

    ControlPanel {
        id: controlPanel
    }

    Connections {
        target: controlPanel
        onOpenChanged: {
            if (controlPanel.open)
                cover = Qt.resolvedUrl("cover/PlayerCover.qml")
            else
                cover = Qt.resolvedUrl("cover/DefaultCover.qml")
        }
    }

    function showMessage(text) {
        if (!applicationActive)
            return

        if (messageLoader.status === Loader.Null)
            messageLoader.source = Qt.resolvedUrl("utils/Message.qml")

        messageLoader.item.show(text)
    }

    function hideMessage() {
        if (messageLoader.status === Loader.Null)
            return

        messageLoader.item.hide()
    }

    function _refresh() {
        _refreshModel.fetch()
    }

    SomaTheme {
        id: somaTheme
    }

    Timer {
        id: refreshTimer
        running: applicationActive || controlPanel.state === "playing"
        repeat: true
        interval: 20000
        onTriggered: _refresh()
    }

    onApplicationActiveChanged: {
        if (applicationActive) {
            _refresh()
        }
    }
}
