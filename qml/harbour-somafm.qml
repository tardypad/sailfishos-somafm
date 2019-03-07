/**
 * Copyright (c) 2013-2014 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
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

    initialPage: Component { FavoritesPage { } }
    cover: DefaultCover { }
    bottomMargin: controlPanel.visibleSize

    Loader {
        id: messageLoader
        anchors.bottom: parent.bottom
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
